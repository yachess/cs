(define fac
    (lambda (x)
        (if (= x 0)
            1
            (* x (fac (- x 1))))))

(print (fac 5))
(exit)
