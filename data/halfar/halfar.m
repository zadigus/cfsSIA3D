% Halfar glacier is the fundamental solution to the shallow ice equation when no surface mass-balance 
% and no sliding apply and when the bedrock topography is defined by zero elevation (hence flat bed, b = 0, B = 0, \Gamma_s = 0)

function z = halfar(x, y, T, H0, R0, t0) 
% Halfar glacier's shape after T/t0 years starting from a horizontal extent R0 and a vertical extent H0; t0 is the glacier's characteristic time
	r = sqrt(x^2+y^2)/R0;
	t = T/t0;
	inside = max(0, 1. - (r / t^(1./18.)).^(4. / 3.));
	z = H0*inside^(3./7.) / t^(1./9.);
endfunction

function [vx, vy, vz] = Velocity(x, y, T, G, H0, R0, t0, H)
	r = sqrt(x^2+y^2)/R0;
	t = T/t0;
	C = 5./4.*G*(4./7.)^3*(H0^7/R0^4)*(1./t)^(5/6);
	vx = vy = vz = 0;
	if(H>0)
		vx = C*x; 
		vy = C*y;
		vz = (4/7)^3*G*H0^8/R0^4*(1/t)^(51/54)*(1-(r*(1/t)^(1/18))^(4/3))^(-4/7)*(15/7*1/t*r^(4/3)-2-2/7*(r*(1/t)^(1/18))^(4/3));
	endif
endfunction

xmin = -3000; xmax = abs(xmin); % simulation's total extent
R0 = 1500; % glacier's horizontal extent
H0 = 250;  % glacier's vertical extent
A  = 0.1;  % rate factor in bar^{-3}*a^{-1}
rho= 910;  % ice density in kg*m^{-3}
n  = 3;    % Glen's exponent
g  = 9.81; % gravitational acceleration in m * s^{-2}
G  = 2*A*(rho*g)^n/(n+2)*10^(-15); % Gamma in consistent units
t0 = 1./(18.*G)*(7./4.)^3*R0^4/(H0^7); % characteristic time in a

dh = [100, 50, 25, 12.5]; % various mesh sizes

for k=1:length(dh)
	surfaceFile = sprintf("surfinit-%g.xyz", dh(k));
	baseFile    = sprintf("base-%g.xyz", dh(k));
	surface1File= sprintf("surface-%g-tf=%g.xyz", dh(k), 1);
	surface10File= sprintf("surface-%g-tf=%g.xyz", dh(k), 10);
	vx0File = sprintf("vx-%g-tf=%g.xyz", dh(k), 0);
	vy0File = sprintf("vy-%g-tf=%g.xyz", dh(k), 0);
	vz0File = sprintf("vz-%g-tf=%g.xyz", dh(k), 0);
	vx1File = sprintf("vx-%g-tf=%g.xyz", dh(k), 1);
	vy1File = sprintf("vy-%g-tf=%g.xyz", dh(k), 1);
	vz1File = sprintf("vz-%g-tf=%g.xyz", dh(k), 1);
	vx10File = sprintf("vx-%g-tf=%g.xyz", dh(k), 10);
	vy10File = sprintf("vy-%g-tf=%g.xyz", dh(k), 10);
	vz10File = sprintf("vz-%g-tf=%g.xyz", dh(k), 10);
	fp1 = fopen(surfaceFile, 'w');
	fp2 = fopen(baseFile, 'w');
	fp3 = fopen(surface1File, 'w');
	fp4 = fopen(surface10File, 'w');
	fp5 = fopen(vx0File, 'w');
	fp6 = fopen(vy0File, 'w');
	fp7 = fopen(vx1File, 'w');
	fp8 = fopen(vy1File, 'w');
	fp9 = fopen(vx10File, 'w');
	fp10 = fopen(vy10File, 'w');
	fp11 = fopen(vz0File, 'w');
	fp12 = fopen(vz1File, 'w');
	fp13 = fopen(vz10File, 'w');
	x = linspace(xmin, xmax, (xmax-xmin)/dh(k)+1);
	for i=1:length(x)
		for j=1:length(x)
			Ht0 = halfar(x(i), x(j), t0, H0, R0, t0); % initial shape
			fprintf(fp1, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, Ht0);
			fprintf(fp2, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, 0);
			Ht1 = halfar(x(i), x(j), t0+1, H0, R0, t0); % shape after one year
			fprintf(fp3, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, Ht1);
			Ht10 = halfar(x(i), x(j), t0+10, H0, R0, t0); % shape after ten years
			fprintf(fp4, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, Ht10);
			[vx, vy, vz] = Velocity(x(i), x(j), t0, G, H0, R0, t0, Ht0); % initial ice velocities
			fprintf(fp5, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vx);
			fprintf(fp6, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vy);
			fprintf(fp11, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vz);
			[vx, vy, vz] = Velocity(x(i), x(j), t0+1, G, H0, R0, t0, Ht1); % ice velocities after one year
			fprintf(fp7, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vx);
			fprintf(fp8, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vy);
			fprintf(fp12, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vz);
			[vx, vy, vz] = Velocity(x(i), x(j), t0+10, G, H0, R0, t0, Ht10); % ice velocities after ten years
			fprintf(fp9, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vx);
			fprintf(fp10, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vy);
			fprintf(fp13, "%g\t%g\t%g\n", x(i)+xmax, x(j)+xmax, vz);
		endfor
		fprintf(fp1, "\n");
		fprintf(fp2, "\n");
		fprintf(fp3, "\n");
		fprintf(fp4, "\n");
		fprintf(fp5, "\n");
		fprintf(fp6, "\n");
		fprintf(fp7, "\n");
		fprintf(fp8, "\n");
		fprintf(fp9, "\n");
		fprintf(fp10, "\n");
		fprintf(fp11, "\n");
		fprintf(fp12, "\n");
		fprintf(fp13, "\n");
	endfor
	fclose(fp1); fclose(fp2); fclose(fp3); fclose(fp4); fclose(fp5); fclose(fp6); fclose(fp7); fclose(fp8); fclose(fp9); fclose(fp10); fclose(fp11); fclose(fp12); fclose(fp13);
endfor
