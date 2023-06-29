(ns app
  (:require [menu])
  (:require [db])
  (:gen-class))

;; Load the data and call the main menu function
(defn -main []
  #_{:clj-kondo/ignore [:inline-def]}
  (def students (db/load-data "studs.txt"))
  #_{:clj-kondo/ignore [:inline-def]}
  (def courses (db/load-data "courses.txt"))
  #_{:clj-kondo/ignore [:inline-def]}
  (def grades (db/load-data "grades.txt"))
  (menu/main-menu students courses grades)
  )

(-main)

;;COMP 348 AB - Assignment 3
;;Done By: Syed Ayaan Jilani

;;Citations :-
;;1) Slides and Lecture notes 
;;2) ClojureDocs (syntax and documentation)
;;3) Stack Overflow (debugging)

;;Notes :-
;;Supressed the clj-kondo warnings by calva 
;;mainly for inline definitions of variable.
;;Better to use "let" binding instead of inline 
;;defs but let is out of scope for this course
