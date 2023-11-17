
data Nat = Zero | Succ Nat

-- NAT value:
    -- an empty box labeled zero
    -- box labeled SUCC with another NAT in it

--Some NAT values:
--Zero
--Succ ZERO
--Succ (Succ Zero)
--Succ (Succ (Succ Zero))

--data Nat = Zero	--	base constructor
--		| Succ Nat --	inductive	constructor

toInt :: Nat -> Int
toInt Zero = 0	--	base	case
toInt (Succ	n) = 1 + toInt	n --	inductive	case

------------------------------------------------------------------------------------
message= "fwewf"

-- DONT DO FOLLOWING (Type Alias)
type Date= (Int, Int, Int)
type Time=(Int, Int, Int)

-- TRY THIS (Product Type)

data Date = Date Int Int Int
data Time = Time Int Int Int


dld :: Date
dld =(4, 20, 2022)

dlt :: Time
dlt = (23, 59, 59)

edl :: Date -> Date
edl date =undefined


-- Record syntax

-- instead of data date = date Int Int Int

-- these are field names
date Date = Date {
    month :: Int,
    day = :: Int,
    year :: Int
}

dld = Date 4 20  2022
dlm = month dld

-- Sum types (Enum types)

-- FOr when you want one of several options
-- 
--Example: represnting text documents where every !!
-- para is one of :
-- - plain text (String)
-- - heading level and text (Int and String)
-- - list (ordered or not) and items (Bool, [String])

dpc = [(1, "My notes from lect 8"), "Sum types are cool", (True, ["apples", "orange"])]

--Problem: This is a heterogenous list!
-- Doesnt type check

{-
Solution: define a type for paragraphs that is a sum of the three options

-}

data Paragraph =
    PlainText String
    | Heading Int String
    | List Bool [String]

doc :: [Paragraph]
doc= [Headinig 1 "My Note", PlainText "Tfwef", List True ["app", "orange"]]

convertToHtml :: Paragraph -> String
convertToHtml (PlainText str) = undefined
convertToHtml (Heading n str) = undefined
convertToHtml (List b items) = undefined

{-
case expressions

p is called as "match scrutinee"

match scrutinee It can be an expression

-}
convertToHtmlAlt :: Paragraph -> String
convertToHtmlAlt p = 
    case p of 
        PlainText str -> undefined 
        Heading n str -> undefined
        List b items -> undefined

{-
Recursive types
for when a value of type T contains
sub-values of the same type T

1. a natural number is either zero 
2. a successor to a natural number
-}

data Nat = Zero | Succ NAT

-- A Nat value is either Zero
-- which is like an empty box labeled "Zero"
-- or its a box labeld "Succ" with another Nat value in it!

{-
:t Zero
:t Succ Zero
-}


toInt :: Nat -> Int
toInt Zero = 0	--	base	case
toInt (Succ	n) = 1 + toInt	n --	inductive	case
--How to install
toInt install zero + succ n total equals the natAdd n m


natadd :: Nat -> Nat -> Nat
natAdd Zero m = m
natAdd (Succ n) m = Succc (natAdd n m )

{-
Sum list is not tail recurisve because

-}

sl :: [Int] -> [Int]
sl l = slh l 0

-- Second args to sl is an accumultor
slh :: [Int] ->Int-> Int
slh []  a= a
slh (x: xs) a = slh xs (a +x)