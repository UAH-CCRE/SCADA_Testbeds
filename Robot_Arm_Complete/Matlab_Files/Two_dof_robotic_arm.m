function theta_ddot=fcn(tau,theta,theta_dot)

g = 9.81;

% Specification of the robot,i.e the mass of each arm and the length of
% each arms
L1 = 1.0;
L2 = 1.0;
m_1 = 1;
m_2 = 1;

%Angular components and projections
c1=cos(theta(1));
s1=sin(theta(1));

c2=cos(theta(2));
s2=sin(theta(2));

c12=cos(theta(1)+theta(2));
s12=sin(theta(1)+theta(2));

%Mass Matrix Implementation

M=[[0,0];[0,0]];

M(1,1) = L2^2*m_2+2*L1*L2*m_2*c2+L1^2*(m_1+m_2);
M(1,2) = L2^2*m_2+L1*L2*m_2*c2;
M(2,1) = L2^2*m_2+L1*L2*m_2*c2;
M(2,2) = L2^2*m_2;

%Centrifugal and Coriolis terms

V=[0;0];

V(1,1) = -m_2*L1*L2*s2*theta_dot(2)^2-2*m_2*L1*L2*s2*theta_dot(1)*theta_dot(2);
V(2,1) = m_2*L1*L2*s2*theta_dot(1)^2;

%Gravity terms

G=[0;0];

G(1,1) = m_2*L2*g*c12+(m_1+m_2)*L1*g*c1;
G(2,1) = m_2*L2*g*c12;

theta_ddot = inv(M)*(tau-V-G);

