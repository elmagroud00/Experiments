ion
	  (char-to-string char)
	  nil
	  t
	  arg)
	 (progn
	   (goto-char
		(if (> arg 0)
			(1 - (point))
		  (1 + (point))))
	   (point))
   (if(> arg 0)
	   (point-max)
	 (point-min))))

(kill-region 1 10)
this-command
(car '(a b c))
(cdr '(a b c))
kill-ring
king-ring-max
(length kill-ring)
kill-ring-max
(setq example-list '("here is a clsue" "another clause"))
(cons "a third clause" example-list)
(setq exmaple-list '("a third clause"))
(setq example-list (cons "a third clause" example-list))
(setq trees '(maple oak pine birch))
(setcdr (nthcdr 2 trees) nil)
trees
kill-ring-yank-pointer
(progn 1 2 3 4)
























