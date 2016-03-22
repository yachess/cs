(defun fib (n)
    (if (<= n 1)
        1
        (+ (fib (- n 1)) (fib (- n 2)))))
(loop for x from 0 to 9 do
    (format t "~D~%" (fib x)))
