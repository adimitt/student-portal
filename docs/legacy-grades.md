Legacy grading notes (pre-overhaul)
===================================

The old portal hardcoded a 5-subject array and a letter-only grade.
Boundaries used by the legacy build:

  90 and above : A
  75 to 89     : B
  60 to 74     : C
  40 to 59     : D
  below 40     : F

Known problems to fix during the overhaul:
  - no GPA on the ten point scale, only letters
  - subject count fixed at 5
  - no rounding rule, values truncated on display
  - grade table duplicated in two places
