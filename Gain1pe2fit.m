[file,path] = uigetfile('*.*'); %ouvre une boite de dialogue pour ouvrir les .dat
File = strcat(path,file); % concatenation chemin fichier
Table = readtable(File);
Array = table2array(Table);
Question = 'Channel to read (0-7)= ??'; %channel choice
Channeltoread = input(Question)         %channel choice          
 Offset = ((Channeltoread)*8)+2;        %channel choice
X = Array (Offset+3,:)                  %channel choice
Y = Array (Offset+5,:)                  %channel choice

X=cell2mat(X);              %data convertion to "fitable" format
X=str2num(X);
Y=cell2mat(Y);
Y=str2num(Y);

f0 = fit(X.',Y.','gauss1')  %fit of the pedestal
Coeff0 = coeffvalues(f0);

N = length (X);         %withdraw of the pedestal fit value from the Data
for i = 1:N
    xval=X(i)
    Yf1(i)= Y(i)-f0(xval)
    "if Yf1(i) <0"
     "   Yf1(i)=0"
    "end"
end;


f1 = fit(X.',Yf1.','gauss1');   %fit of the 1pe
Coeff1 = coeffvalues(f1);


plot(X,Y,'b.',X,Yf1,'g')
hold on;
plot(f1,'r')
plot(f0,'r')
hold off

Mean_0 = Coeff0(2) %moyenne piedestal pC
SdeV_0 = Coeff0(3)/sqrt(2) %sdev piediestal pC
Mean_1 = Coeff1(2)- Coeff0(2) %moyenne 1pe pC
SdeV_1 = Coeff1(3)/sqrt(2)%sdev 1pe pC
Gain_1pe = abs(Mean_1*1e-12/(1.6*1e-19))

x1 = -1;
x2 = 0;
F = @(x) (Coeff0(1)*exp(-((x-Coeff0(2))/Coeff0(3))^2) + Coeff1(1)*exp(-((x-Coeff1(2))/Coeff1(3))^2));
x_min = fminbnd(F,x1,x2);
k = find(X> x_min);
Prob_0= sum(Y(k(1):end))/sum(Y)*100
set(gca, 'YScale','log')
axis ([min(X) max(X) 1 max(Y)])
Title = strrep(file,'_',' ');
 xlabel('Charge (pC)')
 ylabel('nB Hits')
 title({Title ;...
            ['Gain 1pe =',num2str(Gain_1pe)];...
            ['Alpha = ', num2str(Alpha)];...
            ['Mean_1pe = ', num2str(Mean_1),' SdeV_1pe = ', num2str(SdeV_1)];...
            ['Prob "0" = ', num2str(Prob_0)]...
            })
