(defrule data­input
=>
(printout t crlf "Enter flower type (orangereya - 1, opened ground- 2): ")
(bind ?type (read))
(assert (type ?type))
(printout t crlf "Enter temperature of environment (>=3 and <=25): ")
(bind ?temp (read))
(assert (temp ?temp))
(printout t crlf "Enter life length (one year - 1 / two years - 2 / many - 3): ")
(bind ?life (read))
(assert (life ?life)))

(defrule R2
(temp ?temp)
(test (> ?temp 25))
=>
(printout t crlf crlf "Doo you want to boil it?" crlf))

(defrule R1
(type ?type)
(test (or (> ?type 2) (<= ?type 0)))
=>
(printout t crlf crlf "Wrong flower type." crlf))

(defrule R3
(temp ?temp)
(test (< ?temp 3))
=>
(printout t crlf crlf "Too cold for flower :c" crlf))

(defrule R4
(life ?life)
(test (< ?life 1))
=>
(printout t crlf crlf "Flower should live at leat one day..." crlf))

(defrule R5
(life ?life)
(test (> ?life 3))
=>
(printout t crlf crlf "Flower can't live forever..." crlf))

(defrule R6
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (>= ?temp 3) (<= ?temp 6))) (= ?life 1)))
=>
(printout t crlf crlf "Fuksiya" crlf))

(defrule R7
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (>= ?temp 3) (<= ?temp 6))) (= ?life 2)))
=>
(printout t crlf crlf "Pelargoniya" crlf))

(defrule R8
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (>= ?temp 3) (<= ?temp 6))) (= ?life 3)))
=>
(printout t crlf crlf "Kameliya" crlf))

(defrule R9
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (> ?temp 6) (< ?temp 17))) (= ?life 1)))
=>
(printout t crlf crlf "Alternantera" crlf))

(defrule R10
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (> ?temp 6) (< ?temp 17))) (= ?life 2)))
=>
(printout t crlf crlf "Koleus" crlf))

(defrule R11
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (> ?temp 6) (< ?temp 17))) (= ?life 3)))
=>
(printout t crlf crlf "Gnafalium" crlf))

(defrule R12
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (> ?temp 16) (< ?temp 26))) (= ?life 1)))
=>
(printout t crlf crlf "Adiantum" crlf))

(defrule R13
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (> ?temp 16) (< ?temp 26))) (= ?life 2)))
=>
(printout t crlf crlf "Orhideya" crlf))

(defrule R14
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 1) (and (> ?temp 16) (< ?temp 26))) (= ?life 3)))
=>
(printout t crlf crlf "Palma Levistona" crlf))

(defrule R15
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 2) (and (>= ?temp 3) (< ?temp 15))) (= ?life 1)))
=>
(printout t crlf crlf "Aystry" crlf))

(defrule R16
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 2) (and (>= ?temp 3) (< ?temp 15))) (= ?life 2)))
=>
(printout t crlf crlf "Margarytky" crlf))

(defrule R17
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 2) (and (>= ?temp 3) (< ?temp 15))) (= ?life 3)))
=>
(printout t crlf crlf "Liliya" crlf))

(defrule R18
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 2) (and (>= ?temp 15) (<= ?temp 25))) (= ?life 1)))
=>
(printout t crlf crlf "Kalendula" crlf))

(defrule R19
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 2) (and (>= ?temp 15) (<= ?temp 25))) (= ?life 2)))
=>
(printout t crlf crlf "Dzvinochok" crlf))

(defrule R20
(type ?type)
(temp ?temp)
(life ?life)
(test (and (and (= ?type 2) (and (>= ?temp 15) (<= ?temp 25))) (= ?life 3)))
=>
(printout t crlf crlf "Lupun" crlf))