float asin(float c){

float out;

out= ((c+(c*c*c)/6+(3*c*c*c*c*c)/40+(5*c*c*c*c*c*c*c)/112+

(35*c*c*c*c*c*c*c*c*c)/1152 +(c*c*c*c*c*c*c*c*c*c*c*0.022)+

(c*c*c*c*c*c*c*c*c*c*c*c*c*.0173)+(c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*.0139)+

(c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*0.0115)+(c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*c*0.01)

));

//asin

if(c>=.96 && c<.97){out=1.287+(3.82*(c-.96)); }

if(c>=.97 && c<.98){out=(1.325+4.5*(c-.97));} // arcsin

if(c>=.98 && c<.99){out=(1.37+6*(c-.98));}

if(c>=.99 && c<=1){out=(1.43+14*(c-.99));}

return out;}

float acos(float c)

{float out;

out=asin(sqrt(1-c*c));

return out;}

float atan(float c)

{float out;

out=asin(c/(sqrt(1+c*c)));

return out;}