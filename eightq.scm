(define safe
    (lambda (sq queens)
        (define share-row-col
            (lambda (sq1 sq2)
                (if (or (= (quotient sq1 8)(quotient sq2 8))
                        (= (remainder sq1 8)(remainder sq2 8))
                        (= (abs (- (quotient sq1 8)(quotient sq2 8)))
                           (abs (- (remainder sq1 8)(remainder sq2 8)))))
                    #t #f)))
        (if (null? queens)
            #t
            (and (not (share-row-col sq (car queens)))
                (safe sq (cdr queens))))))

(define print-queens
    (lambda (queens)
        (do ((i 0(+ i 1))) ((= i 64))
            (if (member i queens)
                (display "Q ")
                (display ". "))
            (if (= (remainder i 8) 7)
                (newline)))))

(define sol_cnt 0)
(define solve 
    (lambda (queens row)
        (if (= row 8)
            
            (begin 
                (set! sol_cnt (+ sol_cnt 1))
                (print "Solution #:" sol_cnt)
                (print-queens queens)
            #t)
                (do ((i 0(+ i 1))) ((= i 8))
                    (let ((sq (+ (* row 8) i)))
                        (if (safe sq queens)
                            (begin
                                (set! queens (cons sq queens))
                                (solve queens (+ row 1))
                                (set! queens (cdr queens)))))))))

(if (solve '() 0)
    (print "solved"))



