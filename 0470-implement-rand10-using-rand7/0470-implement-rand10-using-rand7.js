/**
 * The rand7() API is already defined for you.
 * var rand7 = function() {}
 * @return {number} a random integer in the range 1 to 7
 */
var rand10 = function() {
    let n = (rand7()-1)*7+rand7();
    while(n>40){
        n = (rand7()-1)*7+rand7()
    }
    return (n-1)%10+1
};