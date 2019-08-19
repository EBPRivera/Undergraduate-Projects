function Main(f, a, b, N, TOL)

fprintf('Choose a method of integrating\n');
fprintf('[1] Composite Trapezoidal Rule\n');
fprintf('[2] Composite Simpson''s Rule\n');
fprintf('[3] Composite Midpoint Rule\n');

user_input = input('Input: ');

switch user_input
    case 1
        CompositeTrap(f, a, b, N, TOL);
    case 2
        CompositeSimps(f, a, b, N, TOL);
    case 3
        CompositeMid(f, a, b, N, TOL);
    otherwise
        fprintf('Invalid Input\n');
    
end

end