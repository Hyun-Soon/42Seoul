#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) : AForm(other.getName(), other.getGradeForSign(), other.getGradeForExec()) {}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		this->setName(other.getName());
		this->setSign(other.getSign());
		this->setGradeForSign(other.getGradeForSign());
		this->setGradeForExec(other.getGradeForExec());
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	(void)executor;
	std::string filename = _target + "_shrubbery";
	std::ofstream file(filename);
	if (file.is_open())
	{
		file << "                                                         .\n"
			 << "                                        .         ;  \n"
			 << "            .              .              ;%     ;;   \n"
			 << "            ,           ,                :;%  %;   \n"
			 << "                :         ;                   :;%;'     .,   \n"
			 << "    ,.        %;     %;            ;        %;'    ,;\n"
			 << "        ;       ;%;  %%;        ,     %;    ;%;    ,%'\n"
			 << "        %;       %;%;      ,  ;       %;  ;%;   ,%;' \n"
			 << "        ;%;      %;        ;%;        % ;%;  ,%;'\n"
			 << "            `%;.     ;%;     %;'         `;%%;.%;'\n"
			 << "            `:;%.    ;%%. %@;        %; ;@%;%'\n"
			 << "                `:%;.  :;bd%;          %;@%;'\n"
			 << "                `@%:.  :;%.         ;@@%;'   \n"
			 << "                    `@%.  `;@%.      ;@@%;         \n"
			 << "                    `@%%. `@%%    ;@@%;        \n"
			 << "                        ;@%. :@%%  %@@%;       \n"
			 << "                        %@bd%%%bd%%:;     \n"
			 << "                            #@%%%%%:;;\n"
			 << "                            %@@%%%::;\n"
			 << "                            %@@@%(o);  . '         \n"
			 << "                           %@@@o%;:(.,'         \n"
			 << "                      `.. %@@@o%::;         \n"
			 << "                        `)@@@o%::;         \n"
			 << "                         %@@(o)::;        \n"
			 << "                        .%@@@@%::;         \n"
			 << "                        ;%@@@@%::;.          \n"
			 << "                        ;%@@@@%%:;;;. \n"
			 << "                    ...;%@@@@@%%:;;;;,..    \n";
		file.close();
		std::cout << filename << " created." << std::endl;
	}
}