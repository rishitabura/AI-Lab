% Facts
player(kohli).
player(dhoni).
player(rohit).
player(bumrah).

batsman(kohli).
batsman(dhoni).
batsman(rohit).

bowler(bumrah).

batting_average(kohli, 50).
batting_average(dhoni, 45).
batting_average(rohit, 40).
batting_average(bumrah, 15).

bowling_average(bumrah, 25).
bowling_average(kohli, 50).
bowling_average(dhoni, 55).
bowling_average(rohit, 60).

% Rules
is_batsman(Player) :-
    batsman(Player),
    batting_average(Player, Avg),
    Avg >= 40.

is_bowler(Player) :-
    bowler(Player),
    bowling_average(Player, Avg),
    Avg < 31.

is_all_rounder(Player) :-
    is_batsman(Player),
    is_bowler(Player).
