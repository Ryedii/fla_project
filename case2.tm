#Q = {q0,q1,q2,t1,t2,t3,t4,t5,f1,f2,f3,f4,f5,f6}
#S = {1}
#G = {1,_,t,r,u,e,s,f,a,l}
#q0 = q0
#B = _
#F = {t4}
#N = 2

q0 __ __ ** t1
q0 1_ 1f ** q1

q1 1f 1f *r q1
q1 11 _1 rr q1
q1 1_ _1 rl q2
q2 11 _1 rl q2
q2 1f 1f ** q1

q1 _f _f ** t1
q1 _1 _1 ** f1
q1 __ __ ** f1
q2 _1 _1 ** f1
q2 _f _f ** t1

t1 _* t* r* t2
t2 _* r* r* t3
t3 _* u* r* t4
t4 _* e* r* t5
t1 __ t_ r* t2
t2 __ r_ r* t3
t3 __ u_ r* t4
t4 __ e_ r* t5

f1 _* f* r* f2
f2 _* a* r* f3
f3 _* l* r* f4
f4 _* s* r* f5
f5 _* e* r* f6
f1 __ f_ r* f2
f2 __ a_ r* f3
f3 __ l_ r* f4
f4 __ s_ r* f5
f5 __ e_ r* f6
