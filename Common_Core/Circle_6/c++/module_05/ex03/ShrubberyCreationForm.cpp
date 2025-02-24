#include "ShrubberyCreationForm.hpp"
#include <fstream>
using std::ifstream;
using std::ofstream;

ShrubberyCreationForm::ShrubberyCreationForm(void) {
}

ShrubberyCreationForm::~ShrubberyCreationForm(void) {
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & cpy) : AForm("ShrubberyCreationForm to " + cpy.getTarget(), 145, 137)
{
	*this = cpy;
}

ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm const & rhs) 
{
	this->_target = rhs.getTarget();
	return *this;
}

ShrubberyCreationForm::ShrubberyCreationForm(string target) : AForm("ShrubberyCreationForm to " + target, 145, 137), _target(target)
{
}

string	ShrubberyCreationForm::getTarget(void) const
{
	return this->_target;
}

void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	string asciiTree = 
	"              ,@@@@@@@,\n"
	"       ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
	"    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
	"   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
	"   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
	"   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n"
	"   `&%\\ ` /%&'    |.|        \\ '|8'\n"
	"       |o|        | |         | |\n"
	"       |.|        | |         | |\n"
	"jgs \\/ .\\/_/__/  ,\\_//__\\\\/.  \\_//__/_";

	ofstream out;

	if (this->getMinExecGrade() < executor.getGrade())
		throw Bureaucrat::GradeTooLowException();
	out.open(this->getTarget() + "_shrubbery");
	out << asciiTree;
}
