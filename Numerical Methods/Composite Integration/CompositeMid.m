function CompositeMid(f, a, b, N, TOL)

actualValue = integral(f,a,b);

fprintf('N\tApprox\tAbsolute Error\n');

for n = 2:2:N
    %Initialization of h
    h = (b-a)/(n+2);
    %Summation function in the Composite Midpoint Rule
    sum = 0;
    for j = 0:n/2
        sum = sum + f(a+(2*j+1)*h);
    end
    %Composite Midpoint Rule Formula
    sol = 2*h*sum;
    %Computes the error
    error = abs(actualValue - sol);
    %Prints the value for each iteration
    fprintf('%2i\t%.7f\t%.7f\n',n+2,sol,error);
    %Program ends when error is within tolerance
    if error <= TOL
        fprintf('The approximation to the integral is within tolerance if %i subintervals are used\n',n);
        return;
    end
end

end