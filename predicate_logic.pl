% Facts
male(john).
male(bob).
female(lisa).
female(anna).

parent(john, lisa).
parent(john, bob).
parent(anna, lisa).
parent(anna, bob).

% Rules
father(X, Y) :- male(X), parent(X, Y).
mother(X, Y) :- female(X), parent(X, Y).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
