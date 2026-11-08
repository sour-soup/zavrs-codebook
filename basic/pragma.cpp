#pragma GCC optimize("Ofast", "no-stack-protector", "no-math-errno", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native,arch=core-avx2,tune=core-avx2")
#pragma GCC ivdep
#pragma GCC optimize ("Ofast") // will make GCC auto-vectorize loops and optimizes floating points better.
#pragma GCC target ("avx2") //can double performance of vectorized code, but causes crashes on old machines.
#pragma GCC optimize ("trapv") // kills the program on integer overflows (but is really slow).