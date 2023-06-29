(ns db
  (:require [clojure.string :as string])
  (:gen-class))

;; Function to load data from a text file
(defn load-data [file-path]
  (->> (slurp file-path)                     ;; Read the file content
       (clojure.string/split-lines)          ;; Split into lines
       (map #(clojure.string/split % #"\|")) ;; Split each line into fields
       (into [])))                           ;; Convert the sequence into a vector

(def weights {"A+" 4.3, "A" 4, "A-" 3.7,
              "B+" 3.3, "B" 3, "B-" 2.7,
              "C+" 2.3, "C" 2, "C-" 1.7,
              "D+" 1.3, "D" 1, "D-" 0.7,
              "F" 0})