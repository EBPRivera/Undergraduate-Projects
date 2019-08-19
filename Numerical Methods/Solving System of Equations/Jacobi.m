function Jacobi(A, B, TOL, N)
    %Algorithm taken from https://www3.nd.edu/~zxu2/acms40390F12/Lec-7.3.pdf
    %Input: Coefficient Matrix A, Vector B, Tolerance TOL, max iteration N

    %Initializes the variables.
    n = length(A);
    X0 = zeros(1,n);
    x = zeros(1,n);
    k = 1;
    
    while k <= N
        %Computes for the value of x_i given the equation from the
        %algorithm.
        for i = 1:n
            summation = 0;
            for j = 1:n
                if j == i
                    continue
                end
                summation = summation + (-A(i,j)*X0(1,j));
            end
            x(1,i) = (1/A(i,i))*summation + B(1,i);
        end
        
        %Checks the stopping criterion.
        for i = 1:n
            max = 0;
            if max > abs(x(1,i)-X0(1,i))
                max = abs(x(1,i)-X0(1,i)); 
            end
        end
        if max < TOL
            %Displays solution.
            for j = 1:n
                fprintf('%2i = %.15f\n',j,x(1,j));
            end
            fprintf('\nNumber of iterations: %2i',k);
            return
        end
        
        k = k+1;
        
        %Sets the value of X0 for the next iteration.
        for i = 1:n
            X0(1,i) = x(1,i);
        end
    end
    
    %Displays solution.
    for j = 1:n
        fprintf('%2i = %.15f\n',j,x(1,j));
    end
    fprintf('\nNumber of iterations: %2i',k);
    
end