%Facts
female(riya).
female(neha).
male(rahul).
male(aditya).
male(mohit).

parent(rahul,aditya).
parent(rahul,mohit).
parent(aditya,riya).
parent(aditya,neha).

%Rules
son(X,Y):-male(X) ,parent(Y,X).
daughter(X, Y):- female(X) ,parent(Y ,X).
sibling(X, Y):-
parent(Z, X) ,parent(Z,Y), X \= Y.