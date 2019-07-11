#!/usr/bin/env python

def increment(x):
    x+=1

def append_one(x):
    x.append(1)

def mod_str(x):
    x = 'yesssss'

def main():
    x = 0

    print( 'before increment, x = ', x )
    increment(x)
    print( 'after  increment, x = ', x )

    xvals = [0,1,2,3,9]
    print( 'before append_one, xvals =' )
    print( xvals )
    append_one(xvals)
    print( 'after  append_one, xvals =' )
    print( xvals )

    s = 'noooooo'
    print( 'before mod_str, s =' )
    print( s )
    mod_str(s)
    print( 'after  mod_str, s =' )
    print( s )

    # BAD: many copies since string is immutable:
    v = "Always"
    for vi in [ "Look", "On", "The", "Bright", "Side", "Of", "Life"]:
        v += vi

    print( 'v is ', v )

    # Good: make a mutable list and join:
    w = "".join( [ "Always", "Look", "On", "The", "Bright", "Side", "Of", "Life"] )
    print( 'w is ', w )


if __name__ == "__main__":
    main()
