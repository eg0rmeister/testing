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

prog:  FUN MAIN '(' idents ')' '{' NEWLINE statements '}'
    ;
stmt: 'print' printexp=expr
    | ident=IDENT ('=') assign=expr
    | execute=expr
    | 'if' ifexp=expr '{' NEWLINE ifstmt=statements '}'
    | 'if' ifexp=expr '{' NEWLINE ifstmt=statements '}' 'else' '{' NEWLINE elsestmt=statements '}'
    | 'if' ifexp=expr '{' NEWLINE ifstmt=statements '}' NEWLINE 'else' '{' NEWLINE elsestmt=statements '}'
    | 'while' '(' while_cond=expr ')' '{' (NEWLINE stmt)* '}'
    ;
expr:   function_ident=IDENT '(' arguments=exprs ')' // FunctionExpression
    |   left=expr op=('*'|'/') right=expr // MulExpression | DivExpression
    |   left=expr op=('+'|'-') right=expr // AddExpression | SubExpression
    |   value=INT // NumberExpression
    |   '(' exp=expr ')' // BraceExpression
    |   variable_ident=IDENT // IdentExpression
    |   left=expr op=('>'|'<'|'=='|'!='|'>='|'<=') right=expr
    |   left=expr op=('&&'|'||') right=expr
    ;
statements: ((stmt NEWLINE)*);

fun: FUN ident=IDENT '(' arguments=idents ')' 
'{' 
    NEWLINE statements
    'return' return_expr=expr
    NEWLINE
'}';

idents: IDENT (',' IDENT)*
      |
      ;

exprs:   expr (',' expr)*
     |
     ;