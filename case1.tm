#Q = {q0,q1,ca,cb,fb,fa,mr,wc,mr2,ill,ml,clr,halt,ill1,ill2,ill3,ill4,ill5,ill6,ill7,ill8,ill9,ill10,ill11,ill12,ill13,ill14}
#S = {a,b}
#G = {a,b,c,_,i,l,e,g,n,p,u,t,|}
#q0 = q0
#B = _
#F = {halt}
#N = 2

q0 a_ a_ r* ca
q0 b_ b_ ** mr2
q0 __ __ ** mr2
ca a_ a_ r* ca
ca b_ b_ r* cb
ca __ __ ** mr2
cb a_ a_ ** mr2
cb b_ b_ r* cb
cb __ |_ r* q1

q1 __ __ l* fb
fb c_ c_ l* fb
fb |_ |_ l* fb
fb a_ a_ l* ml
fb b_ |_ l* fa
fa b_ b_ l* fa
fa a_ aa lr fa
fa __ __ rl mr

mr *a *a r* mr
mr _a _a ** wc
wc _a c_ rl wc
wc __ __ ** q1

ml a_ a_ l* ml
ml __ __ r* clr
clr |_ __ r* clr
clr a_ __ r* clr
clr c_ c_ ** halt

mr2 *_ *_ r* mr2
mr2 __ __ l* ill
ill *_ __ l* ill
ill __ __ r* ill1
ill1 __ i_ r* ill2
ill2 __ l_ r* ill3
ill3 __ l_ r* ill4
ill4 __ e_ r* ill5
ill5 __ g_ r* ill6
ill6 __ a_ r* ill7
ill7 __ l_ r* ill8
ill8 __ __ r* ill9
ill9 __ i_ r* ill10
ill10 __ n_ r* ill11
ill11 __ p_ r* ill12
ill12 __ u_ r* ill13
ill13 __ t_ r* ill14
