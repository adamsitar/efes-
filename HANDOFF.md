# Handoff: Source-level debugging of LETVIS FDP

## Goal & current status

The objective is to step through the FDP programs (primarily **EDD**) in Turbo Debugger with live execution and visible Pascal source. Two halves of that are solved; one is not.

- **Solved:** the programs compile clean with `/V` debug symbols, and TD loads a self-built EXE and displays Pascal source at the entry point. Setting a breakpoint and seeing the right source line works.
- **NOT solved — the blocker:** *a self-compiled binary will not run in the demo directory.* Every self-built EXE tested this session halts during unit initialization and exits with code 1. Because TD's "run" and "step" actually execute the program, stepping dies at the same init point. The only binaries that run are the author's original 1999 demo binaries, which have **no** symbol table and so cannot be source-debugged.

So the entire remaining task is: **produce a self-built binary that both runs in the demo dir and carries `/V` symbols.** Everything below is in service of that.

## Environment & build system

Repo root: `/home/adam/EFES_WIN`. Host is Linux (WSL2); the real target is **native Windows** (DOSBox-X has WSL/X11 quirks the user won't fight — all paths are relative/forward-slash so the folder copies to Windows and runs there). Do not introduce symlinks; Windows copy fails on them.

Four programs: **OPL, EDD, FDA, SERVER**. Folder names match program names except SERVER lives in `fdp.source/FDP/S/`. Shared library tree: `fdp.source/FDP/LIB/` with subfolders `UNIT OOP NET L4 FDP FRM MNU ARCH`.

**DOSBox-X drive mounts** (defined in `dosbox-x.conf`, all relative to repo root):
- `C:` → `fdp.demo/idd/` — demo working dir (data files, the binaries you run, `INST\` config sets)
- `D:` → `BP7/installed/` — Borland Pascal 7: `BPC.EXE` (compiler), `TD.EXE`/`TD286.EXE`/`TDX.EXE` (debuggers), `BP.EXE` (IDE), `OVERLAY.PAS` (RTL source — read it for `OvrResult` codes)
- `E:` → `fdp.source/` — the source tree
- `L:` → `fdp.source/FDP/LIB/` — short alias for the library, so TD `-sd` source paths and `BPC.CFG` `/U` paths stay under DOS's ~126-char command-line limit

**`build-headless.sh <TARGET>`** (TARGET = OPL|EDD|FDA|SERVER, default OPL): computes repo root, `cd`s there, wipes prior `COMPILE.LOG` and the target EXE, then runs DOSBox-X non-interactively with `-c "E:\BUILD.BAT <FOLDER> <PROGRAM>"` and `-exit`. A DOSBox window flashes for ~6 s. It then prints the tail of `fdp.source/COMPILE.LOG` and whether the EXE was produced. Output EXE: `fdp.source/FDP/<folder>/APP/<NAME>.EXE`, plus a matching `.OVR`, `.MAP`, and per-unit `.TPU` files.

**`E:\BUILD.BAT <folder> <program>`** (in `fdp.source/BUILD.BAT`) is the DOS side. It does `D:\BPC.EXE E:\FDP\%1\APP\%2.PAS /V /GD /$Y+ > E:\COMPILE.LOG`. Flag meanings (verified against `BPC` help — do not infer from names):
- `/V` = embed Turbo Debugger symbol table **in the EXE**. This is what makes source-level debugging possible. Without it, debug info stays only in `.TPU` files and TD says "no symbol table". It inflates the EXE substantially (a 126 KB release EXE becomes ~450–900 KB) — **this inflation is mostly debug info, not a sign of broken overlays** (see "corrected assumption" below).
- `/GD` = detailed `.MAP` file only. Despite the name it does **nothing** for in-EXE debug info; `/V` is the real flag.
- `/$Y+` = emit Browser/symbol-reference info.

`build-headless.sh` is the headless wrapper; the identical build runs interactively from inside DOSBox as `E:\BUILD.BAT EDD EDD`. The original author's build was just `BPC APP\EDD.PAS` with **no** `/V` and config driven entirely by `COMP.H` + `BPC.CFG`.

**Per-program `BPC.CFG`** (e.g. `fdp.source/FDP/EDD/BPC.CFG`) sets `/U` (unit dirs), `/I` (include dirs), `/O` (object dirs) using **absolute** paths (`E:\FDP\EDD\APP`, `L:\UNIT`, …). They were changed from relative to absolute this session so TD resolves source from any working directory; the search-order within each list was preserved from the original. Include-path order matters intensely in this codebase (see issue 1 and the historical `IO_ARCH.H` bug in README).

**`debug-x.sh <TARGET>`** is a Linux convenience that builds-if-needed, copies the EXE+OVR into the demo dir, and launches TD with the source-path list. **Note it deploys the non-running self-built binary — it is currently part of the problem, not a tool to trust for "does it run".**

## The core problem, decomposed

A binary built from this source fails to run in `C:\` (the demo dir) for at least two *distinct* reasons that stack. Do not conflate them.

**(A) The `DEBUG` conditional bakes in the original developer's machine paths.** `COMP.H` for each program contains `{$DEFINE DEBUG}` (on by default in the repo). Via `fdp.source/FDP/LIB/FDP/PROGRAM.H`, this sets a path prefix constant: `path_exe = '\xe\e\'` for EDD, `'\xe\o\'` for OPL, etc. (with `DEBUG` **off**, `path_exe = ''`). Every file the program opens is prefixed with this. The overlay loader in `fdp.source/FDP/LIB/UNIT/OVR.PAS` does `OvrInit(path_exe + exe + '.ovr')`, i.e. `OvrInit('\xe\e\edd.ovr')`. That directory does not exist under `C:\`, so the overlay manager fails and the program does `Halt(1)`, printing **"Overlay manager error (-1)"**. The author's shipped demo binaries were built with `DEBUG` **off** (`path_exe = ''`), so they find `edd.ovr` in the current directory and run. So `DEBUG`-on binaries are configured for a 1990s dev machine layout (`E:\e\`, `E:\o\`), not the demo dir.

**(B) Turning `DEBUG` off is necessary but NOT sufficient.** Built with `DEBUG` off (path prefix empty, so the overlay path is correct), and also tested with `DEBUG` off + `DEMO` on (mirroring what the shipped demo presumably was), the binary **still exits at startup** — but *silently*: no "Overlay manager error", an empty stdout capture, and no new `ERR.LOG`. The failure mode is different and undiagnosed. Ruling out one suspect: the copy-protection routine `ochrana_programu` in `fdp.source/FDP/LIB/FDP/FDP_PASS.INC` is gated `{$IFDEF EXE_KEY}{$IFNDEF DEMO}{$IFNDEF DEBUG}`, and **`EXE_KEY` is not defined for EDD**, so that routine is not the cause. The silent-exit cause is the next thing to find.

### Corrected assumption (important — earlier reasoning was wrong)

Mid-investigation it looked like the size inversion (shipped EDD 126 KB vs rebuild 450 KB) proved our build was failing to overlay most units, leaving them in the EXE. That is **probably wrong**: the `/V` debug symbol table alone accounts for most of the bulk, and the overlay machinery appears correctly wired (see next section). Treat "overlays aren't being built" as an *unconfirmed* hypothesis, not a fact. The confirmed facts are only: `DEBUG`-on fails on the dev path; `DEBUG`-off fails silently for an unknown reason.

### Overlay machinery (appears correctly wired — verify, don't assume)

- Overlay-allowed is gated on `_OVR`: `COMP_EXE.H` has `{$IFDEF _OVR} {$O+} {$ENDIF}`. `fdp.source/FDP/LIB/FDP/COMP_EXE.H` has `{$DEFINE _OVR}` active. (The `UTIL/` and `TEST/` copies have it commented — those are other programs.)
- Include chain: each unit starts with `{$I comp.h}`; `EDD/COMP.H` line 4 is `{$I comp_exe.h}`. With build cwd `E:\FDP\EDD` and the `/I` list, `comp.h` resolves to `EDD/COMP.H` and `comp_exe.h` to `LIB/FDP/COMP_EXE.H` — so `_OVR` and `{$O+}` reach the units. (Confirm there is no closer-shadowing `comp.h`/`comp_exe.h`; the EDD folder has a `COMP.BAK` lying around.)
- Unit→overlay placement is via `{$O unitname}` directives, which live in the `.OVL` manifest files (`LIB/FDP/FDP.OVL`, and `UNITS.OVL`/`OOP.OVL`/`NET.OVL`/`EXT.OVL` referenced from the main programs), `{$I`-included into the build. `FDP.OVL` lists ~80 units.
- `OvrResult` codes (from `D:\OVERLAY.PAS`): `ovrOk=0, ovrError=-1, ovrNotFound=-2, ovrNoMemory=-3, ovrIOError=-4, ovrNoEMSDriver=-5, ovrNoEMSMemory=-6`. We see **-1 ovrError** in the `DEBUG`-on case. Note -1 ≠ -2: the message is not strictly "file not found", so confirm whether the `\xe\e\` path yields -1 directly or whether something else about the overlay file/EXE is rejected. This distinction matters.

## Decisive experiments for the next agent

Do these in order; each isolates one variable. Build via `build-headless.sh EDD` (or interactively), deploy the EXE **and** OVR together (they are a matched pair from one compile — mismatch alone gives `ovrError`), then run and observe.

1. **Reproduce the working baseline.** Run the *shipped* EDD (`fdp.demo/idd/INST/IDD/EDD.EXE`+`.OVR`) in the demo dir and confirm it runs. Establishes the target behavior and confirms the demo data/config is sane. (It does run, with EDD config seeded — see issue 3.)

2. **`DEBUG` off + `DEMO` on, watch the SCREEN.** Edit `EDD/COMP.H`: comment `{$DEFINE DEBUG}` → `{ DEFINE DEBUG}`, uncomment `{ DEFINE DEMO}` → `{$DEFINE DEMO}`. Rebuild, deploy, and **run interactively in DOSBox-X watching the actual video output** — the silent-exit failure almost certainly prints to the screen (graphics or text console), which a `> LOG` stdout redirect does **not** capture. This is the single most important untried step. Find the on-screen message, then `grep -arn` the source for it (as done for the RDP and overlay errors) to locate the failing check.

3. **Decide DEBUG/DEMO/symbols matrix.** The end state wanted is "runs in demo dir AND has `/V` symbols". `DEBUG` (the app's dev/release switch, controlling paths and behavior) and `/V` (TD's symbol table) are **independent** — you can and should have `DEBUG` off with `/V` on. Confirm `/V` symbols survive a `DEBUG`-off build and TD still shows source.

4. **If overlays are genuinely suspect**, compare unit overlay status between a clean build and the shipped binary (e.g. inspect the `.MAP`, or toggle `_OVR`/`{$O+}` and watch EXE/OVR sizes and `OvrResult`). Only pursue this if step 2's on-screen message points at overlays.

5. **Revert experiments.** `COMP.H` edits are experiments — `git restore` them when done. Keep the demo dir's running binaries as the shipped ones unless deliberately testing a build.

## Working with the environment directly — do this, don't theorize

The biggest time sinks this session came from reasoning about behavior instead of observing it. Drive DOSBox-X and read the logs yourself.

**Run a program and watch it.** Launch interactively (`./run-x.sh`, or `dosbox-x -conf dosbox-x.conf`) and type `EDD` at `C:\>`. **Watch the screen** — these are graphics-mode programs and they print failure reasons to the display, not always to a file. Take screenshots if needed. For a quick liveness check you can run headless and time it: `dosbox-x -conf dosbox-x.conf -c "EDD > E:\RUN.LOG" -c "exit"` backgrounded — if the DOSBox process stays alive past ~15 s the program reached its interactive UI (good); if it exits fast, it halted at startup. But the redirect misses on-screen output, so use interactive observation for diagnosis.

**Always read `ERR.LOG` after a failure — but trust only today's lines.** The programs *append* to `C:\ERR.LOG` and log their reason for refusing to start. **Gotcha:** seeding from `INST\` plants a 1998-dated `ERR.LOG` from the original author's machine; its stale lines (`ndb.IB not found`, old "System initialized") mislead. **Delete `fdp.demo/idd/ERR.LOG` before reproducing**, then read only freshly-dated lines.

**Trace any error message to its source.** Every halt message is a string literal in the Pascal source. `grep -arn "<message text>" fdp.source/` finds the exact check. Use **`grep -a`** always: many files contain DOS box-drawing bytes (`\xDC` etc. in ASCII-art comment banners) and GNU grep skips them as "binary" without `-a`. This already cost one wasted iteration (the `vytvor_novy_subor`/`IO_NU.INC` episode in the README).

**Match EXE and OVR as a pair.** These are overlaid programs. After any compile, deploy `<NAME>.EXE` and `<NAME>.OVR` *from the same build* together. A fresh EXE against an older OVR gives "Overlay manager error (-1)" by itself, independent of everything above.

**Config sets.** The demo dir holds one program's configuration at a time. Seed with `copy C:\INST\IDD\*.* C:\` for EDD or `copy C:\INST\OPL\*.* C:\` for OPL (inside DOSBox), or copy from `fdp.demo/idd/INST/<set>/` on the host. Seeding also overwrites the binaries with shipped ones, so re-deploy the build afterward. Wrong config = startup failure (EDD without its set logs `There is not defined RDP sector`).

## Issue log (chronological, with resolution status)

1. **"Program has no symbol table"** in TD. Cause: `INST\` holds shipped *symbol-less* EXEs; the data-seeding copy (and `OPL.BAT`/`EDD.BAT`) overwrite the debug build with them. *Resolved:* deploy the debug build **after** seeding; never run the BAT after deploying.
2. **TD shows disassembly, no source.** Cause: debug info recorded source paths relative to the compile dir; TD run from `C:\` couldn't resolve them. *Resolved:* `BPC.CFG` now uses absolute paths and TD is given a `-sd` source-dir list (`E:\FDP\EDD\APP;L:\UNIT;…`). Source now displays. One-time alternative inside TD: Options→Path for source, then Options→Save options (writes binary `TDCONFIG.TD`).
3. **"terminated, exit code 1" on run/step; `ERR.LOG`: "There is not defined RDP sector".** Cause: EDD needs its own config set (`INST\IDD`) seeded; the demo ships OPL-configured. The `@SECTOR` node tag lives in `INST\IDD\USERS.INI`. *Resolved* by seeding EDD config — but this only exposed the deeper problem (5).
4. **`ERR.LOG`: ".\LIST\ndb.IB not found".** Cause: this was a **stale 1998 log line** from the `INST` seed, not the live run (which had died before logging). *Resolved:* methodology — delete `ERR.LOG` before reproducing; the real failure was (5).
5. **"Overlay manager error (-1)" → exit 1.** Cause: the `DEBUG`-on dev path `\xe\e\` for the overlay file (problem A above). **This is the live blocker.** *Not resolved.* Turning `DEBUG` off removes this specific error but reveals a second, silent startup failure (problem B) that is undiagnosed. Producing a runnable + symboled binary is the open task.

## File reference

- `fdp.source/FDP/EDD/COMP.H` — EDD build config: `{$DEFINE DEBUG}`, `{ DEFINE DEMO}`, `{$DEFINE EDD}`, `{$DEFINE IDD}`, etc. (`OPL/`, `FDA/`, `S/` have their own.)
- `fdp.source/FDP/LIB/FDP/PROGRAM.H` — defines `path_exe` per program, gated on `DEBUG`. The source of the `\xe\e\` dev paths.
- `fdp.source/FDP/LIB/UNIT/OVR.PAS` — overlay init (`OvrInit`, `OvrInitEMS`, `OvrSetBuf`); prints "Overlay manager error". Body gated `{$IFDEF _OVR}`.
- `fdp.source/FDP/LIB/FDP/COMP_EXE.H` — `{$DEFINE _OVR}` and `{$IFDEF _OVR}{$O+}{$ENDIF}`.
- `fdp.source/FDP/LIB/FDP/FDP.OVL` (+ `UNITS.OVL`/`OOP.OVL`/`NET.OVL`/`EXT.OVL`) — `{$O unit}` overlay placement manifests.
- `fdp.source/FDP/LIB/FDP/FDP_PASS.INC` — `ochrana_programu` copy-protection (inactive for EDD; `EXE_KEY` undefined).
- `fdp.source/FDP/LIB/FDP/_OFPL_RD.INC` — the RDP-sector check (issue 3).
- `BP7/installed/OVERLAY.PAS` — RTL overlay unit; authoritative `OvrResult` codes.
- `fdp.source/BUILD.BAT`, `build-headless.sh`, `debug-x.sh`, `dosbox-x.conf`, `RUN-X.bat`/`run-x.sh` — the harness.
- `README.md`, `TD-CHEATSHEET.md` — usage and TD keystroke reference (cheatsheet's "Getting in"/"Finding the sources" are current; its run-flow assumes the not-yet-true "self-built binary runs").

## One-line summary for the next session

Source shows in TD; the wall is that **self-built binaries don't run in the demo dir** — `DEBUG`-on bakes dev paths (`\xe\e\`) that break the overlay loader, and `DEBUG`-off hits a second silent startup failure. Next step: build EDD with `DEBUG` off + `DEMO` on + `/V`, **run it interactively and read the on-screen failure**, then trace that message to source.
