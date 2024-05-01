# City race

The citizens of Speedville love racing.
They even love it so much that they elected a new mayor because he promised to organize the biggest race possible.
But now that the mayor has been voted in, he needs your help.

The mayor promised the citizens that the race he will organize will be at least *k* kilometers long.
The city consists of streets, each of which has an assigned length in kilometers.
The racing circuit can either be a multi-lap, in which case multiple laps can be driven,
or just a road from one side of the city to the other.
One street can be used multiple times, but if used multiple times, it has to be in the same direction every time.
You need to decide whether a race of such length can be held in the city.

### Input

The first line of the input contains an integer *T* -- the number of test cases (1 <= *T* <= 1000).

For each test case:

- The first line of each test case contains three integers:
    - *n* -- the number of crossroads connected by the streets (2 <= *n* <= 1000),
    - *m* -- the number of streets (1 <= *m* <= 1000),
    - *k* -- the required minimal length of the circuit (1 <= *k* <= 10^6).
- Each of the following *m* lines contains three integers defining the streets:
    - *u* -- the first end of the street,
    - *v* -- the other end of the street,
    - *l* -- the length of the street in kilometers (1 <= *l* <= 1000).

### Output

For each test case, output a line with a single string:

- "YES" if the race circuit is possible.
- "NO" otherwise.

### Example

#### Input

```
3

5 4 10
1 2 1
2 3 2
3 4 3
4 5 4

3 3 5
1 2 1
2 3 1
3 1 1

3 2 3
1 2 1
2 3 1
```

#### Output

```
YES
YES
NO
```

In the first test case, a race through crossroads 1, 2, 3, 4 and 5 can be set up with length exactly 10.

In the second test case, a multi-lap race through crossroads 1, 2 and 3 can be setup with length at least 5.

In the third test case, no race of length at least 3 can be set up.
