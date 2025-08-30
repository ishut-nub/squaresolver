miau
# Square equation solver
____


## Main purpose

1. Solves square equation by respectively entering a, b and c coefficents in **ax^2 + bx + c = 0**\
For example:
```
Input a
1
Input b
3
Input c
-4
Equation has 2 solutions, -4 and 1
```
2. By editing *tests.txt* file you can add your own parameters to know if the program is working properly
Add parameters by using space bar like this\
*a, b, c, x1, x2, root_count* in this specific order
```
1  3 -4 -4  1  2
```
#### Notes
1. If you know an equation has 1 solution, you have to double it and enter in x1 and x2 spot
2. If it has no roots or an infinite amount of them, enter *NAN* in both x1 and x2
#### Root count notes
1. If an equation has infinite amount of solutions, input **-1** in root count spot
2. If it has 0, 1 or 2 solutions - enter respectively 0, 1 or 2
## Installation (Linux only)
1. Install Git
```
sudo apt install git
```
2. Install g++ compiler
```
sudo apt install g++
```
3. Git clone
```
git clone https://github.com/ishut-nub/squaresolver
```
4. Going into right directory
```
cd squaresolver/solversquare
```
5. Setting up
```
make
```
6. Open
```
./solversquare
```
7. Enjoy
## P.S.
My first every program fully written in C++
