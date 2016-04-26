(define filt
    (lambda (n p x)
        (if (null? x)
            '()
             (if (p n (car x))
                (cons (car x) 
                    (filt n p (cdr x)))
                (filt n p (cdr x))))))

; quick sort test
(define qsort
    (lambda (x)
        (if (null? x)
            '()
            (let ((pv (car x)))
                (let ((small (filt pv > (cdr x)))
                    (large (filt pv < (cdr x))))
                    (append (qsort small) (cons pv (qsort large))))))))

(print (qsort (list -1 -10 100 120 52 3 -22 1 2 3)))
(exit)
