Task
Given a set of strong password policies and then a list of passwords, display for each of them OK or NOK, depending on whether or not all these policies are complied with.

Input
The first line contains a positive integer n, unknown but not too large, representing the number of rules that must be followed. The following n lines contain the definition of a rule, in the following possible formats:

length <min_length> - the password must have min_length characters (inclusive); 0 < min_length
length <min_length> <max_length> - the password must have between min_length and max_length characters (inclusive); 0 < min_length <= max_length
class <min_class_count> - the password must have at least min_class_count different types of characters (lowercase letter, uppercase letter, digit, and other characters); 0 < min_class_count < 5
include <class> - the password must include at least one character from the specified class; class can be a, A, 0, or $, characters denoting the desired class
ninclude <class> - the password must not include any character from the specified class; class follows the same rules as above
repetition <max_count> - the same character can be repeated in consecutive positions at most max_count times; 0 < max_count
consecutive <max_count> - the password can have at most max_count consecutive characters in sequence; 0 < max_count
On the following lines, until EOF, there is one password per line, which will be checked against the specified rules.

Output
For each verified password, display OK if the password complies with ALL specified rules, or NOK if there is at least one rule that is not complied with.
