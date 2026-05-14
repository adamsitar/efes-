unit Types;

{
   translated from C++ definition module types.h

   cardinal type definitions

   Copyright (c) Rastislav B”hmer, 1994

}

INTERFACE

type

  Proc = procedure;
  BytePtr = ^byte;
  CharPtr = ^char;
  StringPtr = ^string;

  short = Integer;
  int = Integer;
  long = LongInt;
  float = Single;

  uchar = Byte;
  ushort = Word;
  uint = Word;
  ulong = LongInt;

  bit_mask = Word;
  index = Word;
  size = Word;
  long_size = LongInt;

  tick_time = LongInt;

  money = Double;
  date_type = LongInt;
  date_str = String;

  coordinate = Integer;
  distance = Integer;

  logic = (NO,YES,OFF,ON,ERR,OK,INVALID,VALID,ZERO,ONE);

  result=logic; {only ERR & OK values valid}

  direction = (Backward, Forward,
                Reverse,  Normal,
                 Output,   Input,
                GetFrom,   PutTo,
             Horizontal,Vertical);


  position = (Inside,Outside,LeftTo,UpTo,RightTo,BelowTo,
              UpLeftTo,UpRightTo,DownRightTo,DownLeftTo);

  bool=boolean;
const
  shortSize       = SizeOf(short);
  charSize        = SizeOf(char);
  intSize         = SizeOf(int);
  longSize        = SizeOf(long);
  floatSize       = SizeOf(float);
  doubleSize      = SizeOf(double);

  ucharSize       = SizeOf(uchar);
  ushortSize      = SizeOf(ushort);
  uintSize        = SizeOf(uint);
  ulongSize       = SizeOf(ulong);

  stringSize      = SizeOf(string);
  byteSize        = SizeOf(byte);
  wordSize        = SizeOf(word);

  bit_maskSize    = SizeOf(bit_mask);
  indexSize       = SizeOf(index);
  sizeSize        = SizeOf(size);
  long_sizeSize   = SizeOf(long_size);

  tick_timeSize   = SizeOf(tick_time);

  realSize        = SizeOf(real);
  moneySize       = SizeOf(money);
  dateSize        = SizeOf(date_type);

  coordinateSize  = SizeOf(coordinate);
  distanceSize    = SizeOf(distance);
  logicSize       = SizeOf(logic);
  resultSize      = SizeOf(result);
  directionSize   = SizeOf(direction);
  boolSize        = SizeOf(bool);

const
  NoIndex = $FFFF;
  NULL = nil;

IMPLEMENTATION

BEGIN
END.