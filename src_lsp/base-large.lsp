
(define nil ())
(define #f 0)
(define #t 1)

(define list (lambda x x))

(define car
    (lambda (x)
        (apply (lambda (x . rest) x) x)))

(define cdr
    (lambda (x)
        (apply (lambda (x . rest) rest) x)))

((lambda (define*)
    (set! define
        (syntax (head . rest)
            (if (pair? head)
                (list begin
                    (list define* (car head) nil)
                    (list set! (car head)
                        (cons lambda (cons (cdr head) rest))))
                (cons define* (cons head rest))))))
 define)

(define (cadr x) (car (cdr x)))
(define (caar x) (car (car x)))
(define (cdar x) (cdr (car x)))
(define (cadar x) (car (cdr (car x))))

(define define-syntax
    (syntax (head . rest)
        (list begin
            (list define (car head) nil)
            (list set! (car head)
                (cons syntax (cons (cdr head) rest))))))

(define (not x) (if x #f #t))

(define-syntax (and . args)
    (if args
        (list if (car args)
            (cons and (cdr args))
            #f)
    #t))

(define-syntax (or . args)
    (if args
        (list if (car args)
            #t
            (cons or (cdr args)))
    #f))

(define (= . args)
    (if args
        (if (number? (car args))
            (or (not (cdr args))
                (and (eq? (car args) (cadr args))
                     (apply = (cdr args))))
            #f)
        #t))

(define (<= . args)
    (if args
        (if (number? (car args))
            (if (cdr args)
                (and (or (= (car args) (cadr args))
                         (< (car args) (cadr args)))
                     (apply <= (cdr args)))
                #t)
            #f)
        #t))

(define (>= . args)
    (if args
        (if (number? (car args))
            (if (cdr args)
                (and (or (= (car args) (cadr args))
                         (> (car args) (cadr args)))
                     (apply >= (cdr args)))
                #t)
            #f)
        #t))

(define-syntax (when test . args)
    (list if test
        (cons begin args)
        nil))

(define-syntax (cond . args)
    (when args
        (if (eq? (caar args) 'else)
            (cons begin (cdar args))
            (list if (caar args)
                (cons begin (cdar args))
                (cons cond (cdr args))))))

(define-syntax (let . args)
    (define (let bindings . body)
        (if bindings
            (list
                (list lambda (list (caar bindings))
                    (apply let (cons (cdr bindings) body)))
                (cadar bindings))
            (cons begin body)))
    (apply let args))

(define (newline) (write-u8 10))

(define (write-string str)
    (define len (string-length str))
    (define (write-from i)
        (when (< i len)
            (write-u8 (string-ref str i))
            (write-from (+ i 1))))
    (write-from 0))
