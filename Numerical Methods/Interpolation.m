%Goal: to write a function that approximates the solution to a given
%function using different interpolation polynomials

function Interpolation(x)

%Asks the for an input based on the message displayed
fprintf('Please choose an interpolation method to use\n(1)Lagrange Interpolation\n(2)Neville''s Method\n(3)Newton''s Divided Difference\n(4)Hermite Interpolation\n(5)Exit\n');
user_input = input('Input: ');

%Based on the user's input, the program asks input for the corresponding
%interpolation method
while user_input ~= 5
    switch user_input
        case 1
            fprintf('\nLagrange Interpolation');
            Lagrange_Interpolation(x);
        case 2
            fprintf('\nNeville''s Method');
            Nevilles_Method(x);
        case 3
            fprintf('\nNewton''s Divided Differences');
            Divided_Differences(x);
        case 4
            fprintf('\nHermite Interpolation');
            Hermite_Interpolation(x);
        case 5
            break;
        otherwise
            fprintf('\nInput invalid');
    end
    
    fprintf('\n\nPlease choose an interpolation method to use\n(1)Lagrange Interpolation\n(2)Neville''s Method\n(3)Newton''s Divided Difference\n(4)Hermite Interpolation\n(5)Exit\n');
    user_input = input('Input: ');
end

fprintf('\n\nProgram Terminated\n');
end

function output = nh_input(is_hermite)
%Input: a boolean to determine if the inputs are needed for non_hermite
%iterpolation or hermite interpolation
%Output: A matrix of the values that was given by the user

    %initialize variables
    user_input = 1;
    A = [];
    B = [];
    C = [];
    
    %Keeps asking the user for inputs until the user has no more left to
    %give
    while user_input ~= 2
        switch(user_input)
            case 1
                %Asks the user for inputs
                fprintf('\nInput the x value: ');
                value_input = input('');
                A = cat(2,A,value_input);
                fprintf('Input the corresponding y value: ');
                value_input = input('');
                B = cat(2,B,value_input);
                
                %If the chosen method is the Hermite interpolation, the
                %program will ask the user for inputs for y'
                if is_hermite == 1
                    fprintf('Input the corresponding y'' value: ');
                    value_input = input('');
                    C = cat(2,C,value_input);
                end

                fprintf('Action?\n(1)Input more values\n(2)Start approximating\n');
                user_input = input('Input: ');
            case 2
                %Preparation for approximation will begin after the user
                %has given enough inputs
                break;
            otherwise
                fprintf('INVALID INPUT\n\nContinue?\n(1)Yes\n(2)No\n');
                user_input = input('Input: ');
        end
    end
    output = cat(1,A,B,C);
end

function Lagrange_Interpolation(x)
    %Algorithm was taken from https://nitishhebbar.wordpress.com/2015/08/06/algorithms-and-flowcharts/
    %Initializes the variables
    matrix_values = nh_input(0);
    n = length(matrix_values);
    sum = 0;
    
    %Computes for the Lagrange Polynomials
    for i = 1:n
        prodfunc = 1;
        for j = 1:n
           if(j~=i)
               prodfunc = prodfunc*(x-matrix_values(1,j))/(matrix_values(1,i)-matrix_values(1,j));
           end
        end
        fprintf('L_%2i = %.15f\n', i, prodfunc);
        sum = sum + matrix_values(2,i)*prodfunc;
    end
    
    %prints the approximation
    fprintf('The approximation is given by %.15f', sum);
end

function Nevilles_Method(x)
    %Algorithm was taken from http://www.aaronschlegel.com/nevilles-method-polynomial-interpolation/
    %Initializes variables
    matrix_values = nh_input(0);
    n = length(matrix_values);
    x_val = matrix_values(1,1:n);
    q = zeros(n,n);
    q(1:n,1) = matrix_values(2,1:n);
    
    %Solves for the given elements of the matrix based on the equation
    %given by Neville's method
    for i = 2:n
        for j = i:n
            q(j,i) = ((x - x_val(j-i+1)) * q(j,i-1) - (x - x_val(j)) * q(j-1,i-1))/(x_val(j) - x_val(j-i+1));
        end
    end
    
    %Prints the table of values
    for i = 1:n
        for j = 1:n
            fprintf('%.15f\t', q(i,j));
        end
        fprintf('\n');
    end
    
    %Prints the approximation
    fprintf('\nThe approximation is given by %.15f', q(n,n));
end

function Divided_Differences(x)
    %Algorithm taken from https://www3.nd.edu/~zxu2/acms40390F12/Lec-3.3.pdf
    %Initializes the variables
    matrix_values = nh_input(0);
    n = length(matrix_values);
    F = zeros(n,n);
    
    %Initializes the matrix
    for i = 1:n
       F(i,1) = matrix_values(2,i); 
    end
    
    %Computes for each element in the matrix based on the formula given by
    %the interpolation method
    for i = 2:n
        for j = 2:i
            F(i,j) = (F(i,j-1)-F(i-1,j-1))/(matrix_values(1,i)-matrix_values(1,i-j+1));
        end
        fprintf('\n');
    end
    
    %Prints the table of divided differences
    fprintf('The table of divided differences is given by\n');
    for i = 1:n
        for j = 1:n
            fprintf('%.15f\t', F(i,j));
        end
        fprintf('\n');
    end
    
    %Computes for P_n(x) and prints the result
    sum = 0;
    for i = 2:n
        var_product = 1;
        for j = 1:i-1
            var_product = var_product*(x-matrix_values(1,j));
        end
        sum = sum + F(i,i)*var_product;
    end
    Px = F(1,1) + sum;
    fprintf('\nThe approximation is given by %.15f', Px);
end

function Hermite_Interpolation(x)
    matrix_values = nh_input(1);
    n = length(matrix_values);
    H = zeros(n*2,n*2);
    z = zeros(1,n*2);

    %Initializes the matrix and the values for z
    for i = 1:n
        H(2*i-1,1) = matrix_values(2,i);
        H(2*i,1) = matrix_values(2,i);
        z(1,2*i-1) = matrix_values(1,i);
        z(1,2*i) = matrix_values(1,i);
    end

    %Computes for divided differences
    for i = 2:2*n
        for j = i:2*n
            if H(j,i-1) == H(j-1,i-1)
                H(j,i) = matrix_values(3,j/2);
            else
                H(j,i) = (H(j,i-1)-H(j-1,i-1))/(z(1,j)-z(1,j-i+1));
            end
        end
        fprintf('\n');
    end
    
    %Prints the table of divided differences of the hermite interpolation
    %method
    for i = 1:2*n
        for j = 1:2*n
            fprintf('%.15f\t',H(i,j));
        end
        fprintf('\n');
    end
    
    %Computes and prints for the approximation
    sum = 0;
    for i = 2:2*n
        var_product = 1;
        for j = 1:i-1
            var_product = var_product*(x-z(1,j));
        end
        sum = sum + H(i,i)*var_product;
    end
    Hx = H(1,1) + sum;
    fprintf('\nThe approximation is given by %.15f', Hx);

end