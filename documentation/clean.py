import os
"""
script to move all output files in a special folder

TO DO: this script:
  catch the error
  this script works the same if it finds and moves files even if it does not find files
"""

lst_files_to_rm= ["*.aux", "*.idx", "*.log", "*.out", "*.synctex.gz"]

for type_file in lst_files_to_rm:  
  print "\nMOVE Latex output files: " + type_file,
  
  #search files with type type_file and move them in the folder Latex_output_files
  #the folder Latex_output_files is not parsed
  os.system("find . -path ./Latex_output_files -prune -o -name "+ type_file +" -exec mv {} Latex_output_files \;")
  
  print ": DONE"
  