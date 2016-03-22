(defun fac(n)
    (if (zerop n)
        1
        (* n (fac (- n 1)))))
(format t "factorial 5:~D~%" (fac 5))
