; Guess the number game
; Author: Youngjin Kim
; For education purpose
;

; Seed random number
(setf *random-state* (make-random-state t))

(setq *x (random 100))
(format t "Guess my number(1..99):~%")
(loop
    (setq a (read))
    (cond ( (> a *x)
                (print "Too great!"))
          ( (< a *x)
                (print "Too small!"))
          ( (eq a *x)
                (print "Correct!")
                (return a))))
