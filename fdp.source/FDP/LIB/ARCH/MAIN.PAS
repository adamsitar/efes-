PROGRAM test;

uses Crt,Types,Error,File_IO,CopyMan;

const
  TenDigits :PChar = '0123456789';
  TenLetters:PChar = 'ABCDEFGHIJ';
var
  t :index;
  m :copy_manager;
  f :byteFile;
  StartAppend :logic;
BEGIN
{!}m.Init;
{
m.StartBlockCopy('D:create.tst',ON,100000);
m.StartFileCopy('D:test.v01','',OFF);
m.StartFileCopy('A:octolib.arj','.',ON,100000);
m.StartFileCopy('test.dat','D:',ON,100000);
m.StartFileCopy('create.v01','D:',OFF,0);
}
m.StartBlockCopy('create.dat',OFF,00000);

{
t:=0;
while not KeyPressed do
  begin
  if (m.CopyStatus and CopyActive)=0 then
    begin
    if t>=23000 then
      break;
    m.SaveBlock(TenDigits,10); Inc(t);
    end;
  m.Refresh;
  end;
}


Assign(f,'test.dat');
FileMode := 0;
Reset(f);
m.CopyBlock(FilePtr(@f),0,FileSize(f));

StartAppend:=NO;
while not KeyPressed do
  begin
  if (m.CopyStatus and CopyActive)=0 then
    if StartAppend=NO then
      begin
      StartAppend:=YES;
      m.SaveBlock(TenLetters,10);
      end
    else
      begin
      Writeln;
      Write('Press Enter to proceed next operation');
      ReadKey;
      Break;
      end;
  m.Refresh;
  end;
Close(f);
m.EndCopy;


{
while not KeyPressed do
  begin
  if (m.CopyStatus and CopyActive)=0 then
    begin
    Writeln;
    Write('Press Enter to proceed next operation');
    ReadKey;
    Break;
    end;
  m.Refresh;
  end;
}
Writeln;
Write('Press Enter to exit APP');
ReadKey;
{!} m.Done;
{!} EM.Done;
END.