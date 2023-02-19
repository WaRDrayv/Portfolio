using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

public class ValidationException : Exception
{
	public List<ValidationResult> ValidationResults { get; private set; }

	public ValidationException(List<ValidationResult> validationResults)
		: base("One or more validation errors occurred.")
	{
		ValidationResults = validationResults;
	}
}
