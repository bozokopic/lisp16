(define (factorial x)
    (if x
        (* x (factorial (- x 1)))
        1))

(factorial 10)
