#ifndef GenericFunctions_h
#define GenericFunctions_h

#define signOf(x) (x >= 0 ? 1 : -1)
#define guard(x, min, max) (x > max ? max : x < min ? min : x)

template<typename T>
T map(T x, T in_min, T in_max, T out_min, T out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif //GenericFunctions_h
