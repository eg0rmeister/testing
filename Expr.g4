grammar Expr;
SPACES
 : [ \t] -> skip
 ;
FUN: 'def';
MAIN: 'main';
NEWLINE : [\r\n]+ ;
INT     : [0-9]+ ;
IDENT   : [a-zA-Z]+ ;

file: (fun NEWLINE)* prog NEWLINE (fun NEWLINE)*;

prog:  FUN MAIN '(' idents ')' '{' NEWLINE ((stmt NEWLINE)*) '}'
    ;
stmt: 'print' printexp=expr
    | ident=IDENT ('=') assign=expr
    | execute=expr
    | 'if' ifexp=expr '{' NEWLINE ((ifstmt=stmt NEWLINE)*) '}'
    | 'if' ifexp=expr '{' NEWLINE ((ifstmt=stmt NEWLINE)*) '}' NEWLINE 'else' '{' NEWLINE ((elsestmt=stmt NEWLINE)*) '}'
    ;
expr:   function_ident=IDENT '(' arguments=exprs ')' // FunctionExpression
    |   left=expr op=('*'|'/') right=expr // MulExpression | DivExpression # left - .expr(0)
    |   left=expr op=('+'|'-') right=expr // AddExpression | SubExpression
    |   value=INT // NumberExpression
    |   '(' exp=expr ')' // BraceExpression
    |   variable_ident=IDENT // IdentExpression
    |   left=expr op=('>'|'<'|'=='|'!='|'>='|'<=') right=expr
    |   left=expr op=('&&'|'||') right=expr
    ;

fun: FUN ident=IDENT '(' arguments=idents ')' 
'{' 
    NEWLINE ((stmt NEWLINE)*)
    'return' return_expr=expr
    NEWLINE
'}';

idents: ident=IDENT ',' rest=idents
      | ident=IDENT
      |
      ;

exprs:   expression=expr ',' rest=exprs
     |   expression=expr
     |
     ;