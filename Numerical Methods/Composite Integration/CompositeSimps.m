function CompositeSimps(f, a, b, N, TOL)

actualValue = integral(f,a,b);

fprintf('N\tApprox\tAbsolute Error\n');

for n = 2:2:N
    %Initialization of values
    h = (b-a)/n;
    XI0 = f(a) + f(b);
    XI1 = 0;
    XI2 = 0;
    for i = 1:n-1
        X = a + i*h;
        if 0 == mod(i,2)
            XI2 = XI2 + f(X);
        else
            XI1 = XI1 + f(X);
        end
    end
    %Composite Simpson's Rule Formula
    XI = h*(XI0 + 2*XI2 + 4*XI1)/3;
    %Computes the error
    error = abs(actualValue - XI);
    %Prints the value for each iteration
    fprintf('%i\t%.7f\t%.7f\n',n,XI,error);
    %Program ends when error is within tolerance
    if error < TOL
        fprintf('The approximation to the integral is within tolerance if %i subintervals are used\n',n);
        return
    end
end

end