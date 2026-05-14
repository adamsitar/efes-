{
‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
€                                                          €
€ TMessage                                                 €
€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹€
}
constructor TMessage.Say (_title: string; _messp: PMess;_size: int;
                          _cl,_bk: int;
                          _beep1, _beep2: pointer;
                          _loops: long; _time_out,_res: pbool;
                          _start_tick: long; _do_it: pointer; _data : pointer
                         );
      var   _Event  : TEvent;
      begin
        inherited Init(_title,'', nil,nil, 0,0, _messp,_size, _cl,_bk, _beep1, _beep2,
                       _loops,_time_out,_res, _start_tick,_do_it,_data
                      );
        Run(_Event);
        Done
      end;
