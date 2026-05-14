(*
procedure hang_up (var p: packet);
begin
  p.ncb.command := $92;
  if wait_ncb_completion (p)
  then
    if p.ncb.retcode = 0
    then
      begin
      end
    else
      begin
      end
    {fi}
  else
    begin
      writeln ('X.25 Handler error - NCB.HANG.UP timed out');
      fatal_error;
      halt(3);
    end
  {fi};
end;


procedure closedown;
begin
  hang_up (control_packet);
  delete_name;
end;


*)