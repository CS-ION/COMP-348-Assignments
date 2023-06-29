(ns menu
  (:require [clojure.string :as string])
  (:require [db :refer [weights]])
  (:gen-class))

;; Function to display the courses
(defn display-courses [courses]
  (doseq [course courses]
    (println course)))

;; Function to display the students
(defn display-students [students]
  (doseq [student students]
    (println student)))

;; Function to display the grades
(defn display-grades [grades]
  (doseq [grade grades]
    (println grade)))

;; Function to display the student record
(defn display-student-record [students courses grades]
  (print "Enter student ID: ")
  (flush)
  #_{:clj-kondo/ignore [:inline-def]}
  (def student_id (read-line))
  #_{:clj-kondo/ignore [:inline-def]}
  (def student_name (first (rest (first (filter #(= student_id (first %)) students)))))
  (if (nil? student_name)
    #_{:clj-kondo/ignore [:redundant-do]}
    (do 
      (println "Student ID Invalid !!"))
    #_{:clj-kondo/ignore [:redundant-do]}
    (do
      (println [student_id student_name])
      #_{:clj-kondo/ignore [:inline-def]}
      (def course_list [])
      (doseq [grade (filter #(= student_id (first %)) grades)] 
        #_{:clj-kondo/ignore [:inline-def]}
        (def course_list (concat course_list [[(second (first (filter #(= (first (rest grade)) (first %)) courses)))
                  (second (rest (first (filter #(= (first (rest grade)) (first %)) courses))))
                  (last (first (filter #(= (first (rest grade)) (first %)) courses)))
                  (second (rest grade))
                  (last grade)
                  ]])) 
      ) 
      (doseq [course (reverse(sort course_list))]
        (println course))
   )))

;; Function to display the GPA of a student (GPA = SUM OF ALL (WEIGHTED_GRADE*NO_CREDITS) / NO OF CREDITS)
(defn calculate-gpa [students courses grades]
  (print "Enter student ID: ")
  (flush)
  #_{:clj-kondo/ignore [:inline-def]}
  (def st_id (read-line))
  #_{:clj-kondo/ignore [:inline-def]}
  (def st_name (first (rest (first (filter #(= st_id (first %)) students))))) 
  (if (nil? st_name)
    #_{:clj-kondo/ignore [:redundant-do]}
    (do
      (println "Student ID Invalid !!"))
    #_{:clj-kondo/ignore [:redundant-do]}
    (do
      #_{:clj-kondo/ignore [:inline-def]}
      (def sum_wt_grs 0)
      #_{:clj-kondo/ignore [:inline-def]}
      (def tot_crd 0)
      (doseq [deets (filter #(= st_id (first %)) grades)] 
        #_{:clj-kondo/ignore [:inline-def]}
        (def crd (Integer/parseInt(get (first (filter #(= (second deets) (first %)) courses)) 3)))
        #_{:clj-kondo/ignore [:inline-def]}
        (def wt (get weights (last deets)))
        #_{:clj-kondo/ignore [:inline-def]}
        (def sum_wt_grs (+ sum_wt_grs (* crd wt)))
        #_{:clj-kondo/ignore [:inline-def]}
        (def tot_crd (+ tot_crd crd))
        )
      (if (= 0 tot_crd)
        (do
          (println "Invalid as student taken 0 credits !!"))
        (do 
          (println [st_id st_name])
          (println ["GPA:" (format "%.2f" (/ sum_wt_grs tot_crd))])
          ))
      ))
  )

;; Function to display the course average (AVG PER SEMESTER = SUM OF ALL WEIGHTED GRADES / NO OF STUDENTS)
(defn course-average [courses grades]
  (print "Enter course (Eg. COMP 232, SOEN 228, etc.): ")
  (flush)
  #_{:clj-kondo/ignore [:inline-def]}
  (def course_name (string/split (read-line) #" "))
  #_{:clj-kondo/ignore [:inline-def]}
  (def course_id (first (first (filter #(= (second course_name) (second (rest %))) courses)))) 
  (if (nil? course_id)
    #_{:clj-kondo/ignore [:redundant-do]}
    (do
      (println "Error! Enter correct course in correct format !!"))
    #_{:clj-kondo/ignore [:redundant-do]}
    (do
      #_{:clj-kondo/ignore [:inline-def]}
      (def sem_map {})
      (doseq [grade (filter #(= course_id (second %)) grades)]
        #_{:clj-kondo/ignore [:inline-def]}
        (def sem (second (rest grade)))
        (if (contains? sem_map sem)
          (do 
            #_{:clj-kondo/ignore [:inline-def]}
            (def prev_sum (first (get sem_map sem)))
            #_{:clj-kondo/ignore [:inline-def]}
            (def new_wt (get weights (last grade))) 
            #_{:clj-kondo/ignore [:inline-def]}
            (def sem_map (assoc sem_map sem [(+ prev_sum new_wt) (inc (second (get sem_map sem)))])))
          (do
            #_{:clj-kondo/ignore [:inline-def]}
            (def sem_map (assoc sem_map sem [(get weights (last grade)) 1]))
            )
          )
        )
      (doseq [item sem_map]
        #_{:clj-kondo/ignore [:inline-def]}
        (def total (first (second item)))
        #_{:clj-kondo/ignore [:inline-def]}
        (def cnt (second (second item))) 
        (println [(first course_name) (second course_name) (first item) (/ total cnt)]))
      ))
  )

;; Function to display the main menu
(defn main-menu [students courses grades]
  (println "\n*** SIS Menu ***")
  (println "------------------")
  (println "1. Display Courses")
  (println "2. Display Students")
  (println "3. Display Grades")
  (println "4. Display Student Record")
  (println "5. Calculate GPA")
  (println "6. Course Average")
  (println "7. Exit")
  (print "Enter an option? ")
  (flush)

  #_{:clj-kondo/ignore [:inline-def]}
  (def option (Integer/parseInt (read-line))) 

  (if (and (< option 7) (> option 0))
    (do
      (case option
        1 (display-courses courses)
        2 (display-students students)
        3 (display-grades grades)
        4 (display-student-record students courses grades)
        5 (calculate-gpa students courses grades) 
        6 (course-average courses grades)
        )(main-menu students courses grades)
      )
    #_{:clj-kondo/ignore [:redundant-do]}
    (do
      (if (== option 7)
         #_{:clj-kondo/ignore [:redundant-do]}
         (do
           (println "Terminating Program !!"))
         (do
           (println "Invalid Value !!")
           (main-menu students courses grades))))
    ) 
)