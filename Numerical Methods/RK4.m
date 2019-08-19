function RK4(a,b,N,init)

    f = @(t,w) 4.*exp(0.8.*t) + 0.5.*w;
    actual_fun = @(t) (4/1.3).*(exp(0.8.*t)-exp(-0.5.*t))+2.*exp(-0.5.*t);

    h = (b-a)/N;
    t = a;
    w = init;
    fprintf('t\tRK4\t\t\tActual\t\tRel.Error\n');
    fprintf('%i\t%.7f\t%.7f\t%.7f\n', t, w, actual_fun(t), abs(actual_fun(t) - w));
    
    for i = 1:N
        K1 = h*f(t,w);
        K2 = h*f(t+h/2,w+K1/2);
        K3 = h*f(t+h/2,w+K2/2);
        K4 = h*f(t+h,w+K3);
        w = w+(K1 + 2*K2 + 2*K3 + K4)/6;
        t = a+i*h;
        
        fprintf('%i\t%.7f\t%.7f\t%.7f\n', t, w, actual_fun(t), abs(actual_fun(t) - w));
    end

end