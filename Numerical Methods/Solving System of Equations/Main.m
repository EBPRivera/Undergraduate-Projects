%Goal: to write a set of functions that takes a system of linear equations 
%and computes for the solution to the system.

function Main(A, B, TOL, N, w)
%Input: Coefficient Matrix A, Vector B, Tolerance TOL, max iteration N, Parameter w.
%Output: a solution to the system of equations given the method chosen by
%the user.

    fprintf('Choose a method to solve the sytem of equations.\n(1) Jacobi\n(2) Gauss-Seidel\n(3) SOR\n(4) Exit\n');
    user_input = input('Input: ');
    
    switch user_input
        case 1
            Jacobi(A, B, TOL, N);
        case 2
            GaussSeidel(A, B, TOL, N);
        case 3
            SOR(A, B, TOL, N, w);
        case 4
            fprintf('Terminating program');
    end

end