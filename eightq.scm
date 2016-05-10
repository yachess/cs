
; eightq.scm - Prints all 8 queens positions in which each queen 
;              isn't attacked each other by using backtracking.
;
; Author Kim Youngjin (yachess@gmail.com)
;
;
; Test is given square is safe from attack of queens(list)
;#lang r5rs     ; uncomment this for racket

(define safe?
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
                (safe? sq (cdr queens))))))

; Print queens in readable form
(define print-queens
    (lambda (queens)
        (do ((i 0(+ i 1))) ((= i 64))
            (if (member i queens)
                (display "Q ")(display ". "))
            (if (= (remainder i 8) 7)
                (newline)))))

(define sol_cnt 0)  ; Global variable to count solutions

; Recursively place queens until find all solutions
(define solve 
    (lambda (queens row)
        (if (= row 8)
            (begin 
                (set! sol_cnt (+ sol_cnt 1))
                (display "solution #:")
                (display sol_cnt)
                (newline)
                (print-queens queens))
            (do ((i 0(+ i 1))) ((= i 8))
                (let ((sq (+ (* row 8) i)))
                    (if (safe? sq queens)
                        (begin
                            (set! queens (cons sq queens))
                            (solve queens (+ row 1))
                            (set! queens (cdr queens)))))))))

(if (solve '() 0)
    (display "solved"))
;(exit) ; Uncomment this for ikarus
