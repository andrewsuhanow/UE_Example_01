

// #include "../Controller/Task/Enum/DailyBhvrPointPos.h"

#pragma once


UENUM(BlueprintType, Blueprintable)
enum class EDailyBhvrPointPos : uint8
{
	random_in_zone				= 0,	//UMETA(DisplayName = "Do action in any point"),
	on_point_rotata_forward		= 1,
	on_point_rotata_random		= 2,
	on_point_shift_around		= 3,	
                                                      	                                             
	offset_1_side_look_forward	= 4,
	offset_1_side_look_on_point	= 5,
	offset_2_side_look_on_point = 6,
		
	offset_rnd_around_look_on_point = 7,// ** like random around fire  (look on point)
	offset_rnd_around_look_out	= 8,
		
	rnd_before_look_on_point	= 9,	// ** like before "StreetDataTable"

	MAX
};

// **												    									   rnd side stand     rnd side stand
// **								  stand point										       	look to Point     look from Point
// **							      rnd around			 ^ 		            @  					 @					^
// **           	     rnd look         @         	     @                  v                @   v   @           \  @  /                                  
// **             ^		  \ ^ /	 	   @. . .@          	                                       \   /              @   @                      
// **    RND     (@)	 <  @  >      @.'RNG'.@          	(X)       (X)      (X)              @>  (X)  <@        <@  (X)  @>            (X)      
// **  Location           / v \        @' ' '@               	                                   /   \              @   @                        
// **                                     @                      	   ^        ^                @   ^   @           /	@  \           ^  ^  ^  ^            
// **                                                                  @        @                    @      		    v                ^  @  ^      
// **        	     
// **        	     
// **     0       1         2             3                  4         5       6					 7				    8				   9



















