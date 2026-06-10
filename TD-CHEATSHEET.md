# Turbo Debugger Cheatsheet

This is a working guide to Turbo Debugger (TD) as used in this repository: debugging the LETVIS FDP programs inside DOSBox-X. TD is Borland's standalone source-level debugger, sitting on `D:\` next to the BP7 compiler. It reads the debug symbols that `/V` embeds in the EXE, shows you the original Pascal source, and lets you step, break, and inspect — all from a text-mode UI that predates every convention you're used to, which is why this document exists.

One fact shapes the whole workflow: **the shipped demo binaries have no debug symbols.** You can only source-debug an EXE you built yourself. So the cycle is always: build with `./build-headless.sh <TARGET>` on the host, swap the fresh EXE into the demo directory (the programs need the data files that live there), then debug from `C:\`.

## Getting in

From the host, build and swap in the program you want to debug, then launch DOSBox-X:

```
./build-headless.sh OPL
cp fdp.demo/idd/OPL.EXE fdp.demo/idd/OPL.EXE.orig    # first time only
cp fdp.source/FDP/OPL/APP/OPL.EXE fdp.demo/idd/
./run-x.sh
```

At the `C:\>` prompt, `D:\` is already on PATH. If this is a fresh demo directory, run the program's BAT once (`OPL.BAT`) so it seeds its data files from `INST\` — the BAT just copies `INST\OPL\*.*` into the working directory and runs the program with no arguments. After that, load the debugger directly:

```
TD OPL.EXE
```

If symbols are present you land in the **Module window** showing Pascal source, with an arrow at the program's first `begin`. If instead you get a CPU/disassembly window and a *"Program has no symbol table"* message, the EXE wasn't built with `/V` — you're probably looking at the shipped binary, not yours.

If TD complains about memory (these EXEs are ~900 KB with symbols), use `TDX OPL.EXE` instead — same debugger, DPMI-hosted, much more room. Ignore `TD286` and `TD386`; they need driver setup that doesn't apply under DOSBox-X.

To leave the debugger, **Alt+X**. To restart the program from the beginning without leaving, **Ctrl+F2** (Program reset).

## Finding the sources

The debug info records source paths relative to the directory the program was *compiled* in (`E:\FDP\OPL` for OPL, `E:\FDP\EDD`, `E:\FDP\FDA`, `E:\FDP\S` for the others). Since you run TD from `C:\`, TD can't resolve paths like `..\LIB\UNIT\IO.PAS` on its own and will tell you a module has no source. Fix it once: **Options → Path for source...** and enter the compile directory, e.g. `E:\FDP\OPL`. Then **Options → Save options...** writes a `TDCONFIG.TD` into the current directory so every future session picks it up automatically. (Equivalent one-shot: launch as `TD -sdE:\FDP\OPL OPL.EXE`.)

## The UI in one paragraph

**F10** opens the menu bar (or Alt+highlighted-letter goes straight to a menu); **Esc** backs out. Every window also has its own context menu on **Alt+F10** — this is the single most important key in TD; most window-specific commands live there, each with a Ctrl+letter shortcut you'll learn over time. **F6** cycles between open windows, **Alt+1..9** jumps to a window by its number, **Tab** moves between panes inside a window, **F5** zooms the current window full-screen, **Alt+F3** closes it. **F1** is context help. New windows open from the **View** menu: Module, Watches, Variables, Stack, Breakpoints, CPU, Dump.

## Running and stepping

| Key | Action |
|---|---|
| F7 | Trace into — step one line, descending into calls |
| F8 | Step over — step one line, executing calls whole |
| Alt+F8 | Until return — run to the end of the current routine ("step out") |
| F4 | Go to cursor — run until execution reaches the cursor line |
| F9 | Run — go until a breakpoint, the end, or you interrupt |
| Ctrl+Break | Interrupt a running program and return to TD |
| Ctrl+F2 | Program reset — reload and start over |
| Alt+F7 | Trace one machine instruction (drops into CPU view) |

The arrow in the Module window's left margin marks the current execution point. If you scroll away and lose it, **Ctrl+O** (Origin) brings you back to it.

## Breakpoints

Put the cursor on an executable line and press **F2** — the line highlights. F2 again removes it. To break on a routine by name without hunting for its source, **Alt+F2** (Breakpoints → At...) and type the identifier, e.g. `vytvor_novy_subor`.

For anything fancier, open **View → Breakpoints**: the window lists all breakpoints, and its Alt+F10 local menu has *Set options...*, where you can attach a **condition** (a Pascal expression — break only when `pocet > 10`) and a **pass count** (break only on the Nth hit). *Delete all* lives on the Breakpoints menu.

The Breakpoints menu also offers *Changed memory global...* and *Expression true global...* — watchpoints that stop wherever a variable changes or an expression becomes true. They work by single-stepping the whole program, which under emulation is slow enough that you should reach for them only when genuinely stuck on "who is corrupting this variable."

## Looking at data

The fastest tool is the **Inspector**: in the Module window, put the cursor on any variable and press **Ctrl+I** (or Alt+F10 → Inspect). For a record you get all fields; for a pointer, the pointed-to value — press **Enter** on any field to open a sub-inspector and follow chains of records and pointers as deep as you like; **Esc** climbs back out. For a quick look at scalars this beats watches every time.

- **Ctrl+F4** — Evaluate/modify: type any Pascal expression, see its value, and optionally assign a new one to a variable. Works with the full expression syntax including array indexing and field access.
- **Ctrl+F7** — Add watch: the expression stays visible in the Watches window and updates on every step. Append a format suffix to control display: `,h` hex, `,d` decimal, `,s` string, `,r` record with field names, `,m` raw memory dump.
- **View → Variables** — two panes: globals of the current module, and locals of the current routine. Good for "what's in scope right now."
- **View → Stack** — the call chain. The local menu's *Inspect* on any frame jumps the Module window to that frame's source position, and *Locals* shows that frame's variables. Essential for "how did I get here."
- **Data → Function return** — after Alt+F8, shows what the routine is about to return.

## Navigating this codebase

This source tree leans heavily on `$I` textual includes — a unit like `IO.PAS` pulls in `ERR_LOG.INC`, `IO_NU.INC` and friends, and `BGIGRAPH.PAS` is mostly `.INC` files. The Module window handles this: **F3** (View → Module...) lists all units in the EXE and switches between them; within a module, **Ctrl+F** (local menu → File...) lists the *include files* belonging to it so you can view and set breakpoints inside `.INC` code. **Ctrl+G** jumps to a line number, **Ctrl+S** searches for text and **Ctrl+N** repeats the search.

## Graphics programs and the screen

OPL and EDD draw with BGI graphics, and TD shares the one emulated display with them. **Alt+F5** flips to the user screen so you can see what the program has drawn; any key returns to TD. While stepping through drawing code, TD's default "Smart" swapping can leave either screen garbled — set **Options → Display options... → Display swapping → Always**, which swaps screens around every single step. It flickers, but both screens stay intact.

Two DOSBox-X notes: a click into the window captures the mouse (Ctrl+F10 releases it), and TD itself is happy with the mouse — you can click menus, drag window borders, and right-click for the local menu, which is often quicker than the key chords while you're learning.

## When something is off

*"Program has no symbol table"* — the EXE lacks `/V` debug info; rebuild with `./build-headless.sh` and re-swap. *Source lines don't match what executes* — the EXE in `C:\` is older than the sources you're reading; rebuild and re-swap. *"Module not found" / blank module list entries* — source path not set; see "Finding the sources" above. *Out of memory loading* — use `TDX`. *Program is running and won't stop* — Ctrl+Break; if the program is stuck reading the network or a timer loop, a breakpoint placed via Alt+F2 on a routine you know it must pass through is more reliable. And if the debuggee crashes hard enough to wedge the DOS session, just Alt+X out, quit DOSBox-X, and `./run-x.sh` again — the emulator makes crashes cheap.
