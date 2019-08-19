%Goal: to write a function that approximates the solution to a given
%function using Secant method

function p = SecantMethod(f, p0, p1, TOL, N)
%Input: A function f. Initial points p0 and p1. Tolerance TOL. Maximum
%iterations N
%Output: Table of solution values approximated by the Secant method

%User Error Checking
if nargin < 5
    error('Too few arguments were given'); 
end
if nargin > 5
    error('Too many arguments were given');
end
%User Error Checking End

%Draws the graph of the function in the interval [0, 5]
fplot(f,[0 5]);

%Initializes i, q0, and q1 -> Step 1
i = 2;
q0 = f(p0);
q1 = f(p1);

%Prints the labels of the table then the approximate solutions at the first
%2 iterations
fprintf('Iter\t Approximate Solution\n');
fprintf('%2i\t%f\n',i-1, p0);
hold on;
plot(p0, f(p0), 'r*')
fprintf('%2i\t%f\n',i , p1);
hold on;
plot(p1, f(p1), 'r*')

while(i < N) %Repeats step 3-6 while i < N -> Step 2
    
   %Checks if the value of q1-q0 = 0. If that's the case, the method will
   %fail and the algorithm will end
   if (q1-q0) == 0 || isnan(q1-q0)
       fprintf('The method fails at iteration %2i', i);
       return;
   end
   
   %Sets the value of p -> Step 3; prints the current approximate solution
   %at the current iteration
   p = p1 - (q1 * (p1 - p0)/(q1 - q0));
   fprintf('%2i\t%.15f\n',i+1, p);
   
   %The method succeeds if after N iterations the approximate solution
   %passes given a certain tolerance
   %Prints out the final approximate solution -> Step 4
   if abs(p - p1) < TOL && i == N
       fprintf('The method was successful having the point %f\n', p);
       return;
   end
   
   %Increment i -> Step 5
   i = i+1;
   %Updates p0, q0, p1, q1 -> Step 6
   p0 = p1;
   q0 = q1;
   p1 = p;
   q1 = f(p);
   
   %Plots the point at the current approximate solution
   hold on;
   plot(p, f(p), 'r*');
end