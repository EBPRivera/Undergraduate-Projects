function CompositeTrap(f, a, b, N , TOL)

actualValue = integral(f,a,b);

fprintf('N\tApprox\tAbsolute Error\n');

for n = 1:N
    %Initialization of h
    h = (b-a)/n;
    %Summation function in the Composite Midpoint Rule
    sum = 0;
    for j = 1:n-1
        sum = f(a+j*h) + sum;
    end
    %Composite Trapezoidal Rule Formula
    sol = (h/2)*(f(a) + 2*sum + f(b));
    %Computes the error
    error = abs(actualValue - sol);
    %Prints the value for each iteration
    fprintf('%2i\t%.7f\t%.7f\n',n,sol,error);
    %Program ends when error is within tolerance
    if error <= TOL
        fprintf('The approximation to the integral is within toerance if %i subintervals are used\n',n);
        return
    end
end

end