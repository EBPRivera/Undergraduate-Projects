%Goal: to write a function that approximates the solution to a given
%function using Newton's method

function p = NewtonsMethod(f, f1, p0, TOL, N)
%Input: A function f and it's derivative f1. An initial point p0. tolerance
%TOL. Number of iterations N
%Output: A table of solution values approximated by Newton's method

%User Error Checking
if nargin < 5
    error('Too few arguments were given'); 
end
if nargin > 5
    error('Too many arguments were given');
end
%User Error Checking End

%Draws the graph of the function in the interval [0, 5]
fplot(f, [0 5]);
%Plots the point in the graph
hold on;
plot(p0, f(p0),'r*');

%Initializes i -> Step 1
i = 1;

%Prints the labels for the table and prints the first approximate solution
fprintf('Iter\tApproximate Solution\n');
fprintf('%2i\t%f\n', i, p0);

while(i < N) %Repeats step 3-6 while i < N -> Step 2
    
   %Checks if the value of the first derivative is 0. If that's the case,
   %the method will fail and the algorithm will end
   if f1(p0) == 0 || isnan(f1(p0))
      fprintf('The method fails at iteration %2i', i);
      return;
   end
   
   %Sets the value of p -> Step 3; prints the approximate solution at
   %the current iteration
   p = p0 - f(p0)/f1(p0);
   fprintf('%2i\t%.15f\n', i+1, p);
   
   %The method succeeds if after N iterations the approximate solution
   %passes given a certain tolerance
   %Prints out the final approximate solution -> Step 4
   if abs(p-p0) < TOL && i == N
       fprintf('The method was successful having the approximate solution %f\n', p);
       return;
   end
   
   %Increment i -> Step 5
   i = i + 1;
   %Update p0 -> Step 6
   p0 = p;
   
   %Plots the point at the current approximate solution
   hold on;
   plot(p, f(p), 'r*');
end