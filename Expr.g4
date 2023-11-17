grammar Expr;
SPACES
 : [ \t] -> skip
 ;
FUN: 'def';
MAIN: 'main';
NEWLINE : [\r\n]+ ;
INT     : [0-9]+ ;
IDENT   : [a-zA-Z]+ ;

file: fun* NEWLINE prog;

prog:  FUN MAIN '(' idents ')' '{' NEWLINE ((stmt NEWLINE)*) '}'
    ;
stmt: 'print' printexp=expr
    | ident=IDENT ('=') assign=expr
    | execute=expr
    ;
expr:   function_ident=IDENT '(' arguments=exprs ')' // FunctionExpression
    |   left=expr op=('*'|'/') right=expr // MulExpression | DivExpression # left - .expr(0)
    |   left=expr op=('+'|'-') right=expr // AddExpression | SubExpression
    |   value=INT // NumberExpression
    |   '(' exp=expr ')' // BraceExpression
    |   variable_ident=IDENT // IdentExpression
    ;

fun: FUN ident=IDENT '(' arguments=idents ')' '{' NEWLINE ((stmt NEWLINE)*) '}';

idents: IDENT ',' idents
      | IDENT
      |
      ;

exprs:   expr ',' exprs
     |   expr
     |
     ;