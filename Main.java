public class Main{
    public static void main(String[] args){
	if(args.length != 1){
	    System.out.println("USAGE: java -Djava.library.path=. Main ");
	    return ;
	} 

	if(isContain44greaterNos(args[0])){
	    //if more than 44 consecutive digits are given then espeak would fail
	    System.out.println("NOTE: should not contain more than 44 consecutive digits");
	    return ;
	}

	System.loadLibrary("javaSpeak"); 
	javaSpeak.initialize() ;

	javaSpeak.setPitch(99) ;
	javaSpeak.setRange(99) ;

	javaSpeak.speakText(args[0]); 
	javaSpeak.synchronize();
	javaSpeak.terminate(); 
    }

    private static boolean isContain44greaterNos(String numCheck){
	return numCheck.matches("\\d{45,}") ;

    }
}

