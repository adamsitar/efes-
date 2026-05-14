function size_strany_editora(riadkov,znakov: word): word;
   begin
     size_strany_editora:= riadkov*(znakov+1)+1  { + 1 je len kvoli ladeniu }
   end;

function alloc_stranu_editora(riadkov,znakov: int): pointer;
   var   strana : pointer;
         size : word;
         i : int;
   begin
     size:= size_strany_editora(riadkov,znakov);
     GetMem(strana,size); fillchar(strana^,size, 0);
     for i:= 0 to riadkov-1 do zmaz_stranu_editora(strana, znakov, i,0);
     alloc_stranu_editora:= strana
   end;

procedure dealloc_stranu_editora(var strana: pointer; riadkov,znakov: int);
   begin
     FreeMem(pointer(strana),size_strany_editora(riadkov,znakov));
     strana:= nil
   end;

procedure zmaz_stranu_editora(strana: pointer; znakov: int; r,od: int);
    var   p: pchar;
    begin
      p:= index_pola_s(strana,znakov, r,0, false);
      p^:= chr(znakov);
      p:= p + od+1;
      fillchar(p^,N(znakov-od),' ')
    end;

procedure init_editor_bt(E: PEditors);
    var   bt1: PbtOk;
          bt2: PbtCancel;
          bt3: PDialogButton;
          xt,yt, yi,c : int;
    begin
      with E^ do
        begin
          Win^.get_btXY(0,0, xt,yt);
          bt1:= New(PbtOK, Init(Win,xt,yt, kbCtrlEnter));

          Win^.get_btXY(0,1, xt,yt);
          bt2:= New(PbtCancel,Init(Win,xt,yt));
        end;
    end;


const medzera_ed = 2;
