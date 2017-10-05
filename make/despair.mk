# despair.mk: where everything I shouldn't do in a Makefile gets hidden.

# Convert a string to lowercase.
#
# Usage: $(call lowercase,STRING)
lowercase = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

# Convert a string to uppercase.
#
# Usage: $(call uppercase,STRING)
uppercase = $(subst a,A,$(subst b,B,$(subst c,C,$(subst d,D,$(subst e,E,$(subst f,F,$(subst g,G,$(subst h,H,$(subst i,I,$(subst j,J,$(subst k,K,$(subst l,L,$(subst m,M,$(subst n,N,$(subst o,O,$(subst p,P,$(subst q,Q,$(subst r,R,$(subst s,S,$(subst t,T,$(subst u,U,$(subst v,V,$(subst w,W,$(subst x,X,$(subst y,Y,$(subst z,Z,$1))))))))))))))))))))))))))

# Get parameters that are specific to a given rule for a variable. E.g.,
# the src/kernel.exe-specific LDFLAGS.
#
# E.g., if $@ is src/kernel.exe and you want the LDFLAGS for it,
#       then $(call rule_var,$@,LDFLAGS) returns KERNEL_EXE_LDFLAGS.
#
# Usage: $(call rule_var,$@,LDFLAGS)
# Wrap in ${} to actually get the value of the variable.
rule_var = $(call uppercase,$(subst .,_,$(patsubst src/%,%,$1))_$2)
